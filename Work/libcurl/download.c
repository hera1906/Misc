#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <systemd/sd-journal.h>

#include "download.h"

#define UNUSED(x) (void)(x)

struct myprogress
{
    volatile int *progress; // Progress of downloado (0-100) if not null.
    volatile int *cancel; // Set to non-zero to cancel download if not null
};

#define URL_MAXLENGTH 1000

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

static int xferinfo(void *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
    UNUSED(ultotal);
    UNUSED(ulnow);

    struct myprogress *myp = (struct myprogress *) p;

    if (myp->progress != NULL && dltotal != 0)
    {
        int percentage = (dlnow * 100L) / dltotal;
        if (percentage > 99)
            percentage = 99; // Progress 100 is set from the download function
       *myp->progress = percentage;
    } // if

    if (myp->cancel != NULL && *myp->cancel)
        return 1; // Aborts transfer

    return 0; // Continue transfer
} // xferinfo

//! Download the file at the given url to the given path on the disk.
//! The function writes an entry to the system log
//! \param url Download a file from this url
//! \param path Path of the file that will be created
//! \param progress If not NULL, then this value will be updated with the progress (0-100)
//! \param cancel If not NULL, then setting this value to non-zero will cancel the download
//! \returns 0 if successful, non-zero in case of error
int download(const char *url, const char *path, volatile int *progress, volatile int *cancel)
{
    CURL     *curl;
    FILE     *stream;
    CURLcode status;
    long     response_code;
    char     *redirect_url;
    char     new_url[URL_MAXLENGTH+1];
    volatile struct myprogress myprogress;
 
    sd_journal_print(LOG_NOTICE, "Download: Downloading %s to %s", url, path);

    // Initialize
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
 
    // Set URL
    curl_easy_setopt(curl, CURLOPT_URL, url);

 #ifdef SKIP_PEER_VERIFICATION
     // If you want to connect to a site who isn't using a certificate that is
     // signed by one of the certs in the CA bundle you have, you can skip the
     // verification of the server's certificate. This makes the connection
     // A LOT LESS SECURE.
    
     // If you have a CA cert for the server stored someplace else than in the
     // default bundle, then the CURLOPT_CAPATH option might come handy for
     // you.
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
     
#ifdef SKIP_HOSTNAME_VERIFICATION
     // If the site you're connecting to uses a different host name that what
     // they have mentioned in their server certificate's commonName (or
     // subjectAltName) fields, libcurl will refuse to connect. You can skip
     // this check, but this will make the connection less secure.

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif 

    // Switch on full protocol/debug output while testing
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
 
    // Send all data to this function
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 

    // Function called as download progresses
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo);

    // Structure to deliver to the xferinfo function
    myprogress.progress = progress;
    myprogress.cancel = cancel;
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &myprogress);

    // Enable progress handling if needed
    if (progress != NULL || cancel != NULL)
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    else
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    stream = fopen(path, "wb");
    if (stream == NULL)
    {
        sd_journal_print(LOG_ERR, "Download: Could not open %s for writing", path);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return -1;
    } // if
 
    // Write the body to this stream
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
 
    // Perform the request
    status = curl_easy_perform(curl);

    fclose(stream);

    if (status != CURLE_OK)
    {
        sd_journal_print(LOG_ERR, "Download: Failed with status %d: %s", 
                                  status, curl_easy_strerror(status));
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return status;
    } // if
  
    // Check for redirect:
    status = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (status != CURLE_OK)
    {
        sd_journal_print(LOG_ERR, "Download: Getinfo of response code failed with status %d: %s", 
                                  status, curl_easy_strerror(status));
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return status;
    } // if

    if ((response_code / 100) == 3) // All 3xx codes means redirection
    {
        // redirect
        status = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redirect_url);
        if ((status != CURLE_OK) || redirect_url == NULL)
        {
            sd_journal_print(LOG_ERR, "Download: Getinfo of redirect url failed with status %d: %s", 
                                    status, curl_easy_strerror(status));
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return status ? (int) status : -1;
        } // if

        // Copy redirect url because we clean up curl below
        strncpy(new_url, redirect_url, 1000);
        new_url[URL_MAXLENGTH] = '\0';

        // Prepare to call this recursively:
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        return download(new_url, path, progress, cancel);
    }  // if

    /* cleanup curl stuff */ 
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    status = (response_code / 100) - 2; // All 2xx codes means success
    if (status == 0)
    {
        sd_journal_print(LOG_NOTICE, "Download: Succeeded with HTTP response %d", (int) response_code);
        if (progress != NULL)
            *progress = 100;
    }
    else
    {
        sd_journal_print(LOG_ERR, "Download: Failed with HTTP response %d", (int) response_code);
        status = response_code;
    }
 
    return status; // Will be 0 if ok
} // download

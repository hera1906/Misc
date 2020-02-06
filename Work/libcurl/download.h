#ifdef __cplusplus
extern "C" {
#endif

#define DOWNLOAD_ABORTED 42 /* CURLE_ABORTED_BY_CALLBACK */

//! Download the file at the given url to the given path on the disk.
//! The function writes an entry to the system log
//! \param url Download a file from this url
//! \param path Path of the file that will be created
//! \param progress If not NULL, then this value will be updated with the progress (0-100)
//! \param cancel If not NULL, then setting this value to non-zero will cancel the download
//! \returns 0 if successful, non-zero in case of error. If it is DOWNLOAD_ABORTED, then the download was cancelled
int download(const char *url, const char *path, volatile int *progress, volatile int *cancel);

#ifdef __cplusplus
}
#endif

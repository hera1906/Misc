#include <stdio.h>
#include <sys/time.h>
#include <sys/timex.h>
#include <iostream>

using namespace std;

ssize_t format_timeval(struct timeval *tv, char *buf, size_t sz)
{
    ssize_t written = -1;
    struct tm *gm = gmtime(&tv->tv_sec);
   
    if (sz > 0) 
        *buf = '\0';
    if (gm)
    {
        written = (ssize_t)strftime(buf, sz, "%Y-%m-%dT%H:%M:%S", gm);
        if ((written > 0) && ((size_t)written < sz))
        {
            int w = snprintf(buf+written, sz-(size_t)written, ".%06dZ", tv->tv_usec);
            written = (w > 0) ? written + w : -1;
        }
    }
    return written;
} // format_timeval

int main() 
{ 
    struct ntptimeval ntv;
    char buf[100];


    int status = ntp_gettime(&ntv);

    format_timeval(&ntv.time, buf, sizeof(buf));

    cout << "ntp_gettime : returned " << status << endl;
    cout << "              time: " << buf << endl;
    cout << "              maxerror: " << ntv.maxerror << " us" << endl;
    cout << "              esterror: " << ntv.esterror << " us" << endl;
    cout << "              tai     : " << ntv.tai << endl;

} // main

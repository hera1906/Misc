#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <sys/timex.h>
#include <ctime>
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
    char buf[100];
    struct timeval delta;
    struct ntptimeval ntv;


    int status = ntp_gettime(&ntv);

    format_timeval(&ntv.time, buf, sizeof(buf));

    cout << "ntp_gettime : returned " << status << endl;
    cout << "              time: " << buf << endl;
    cout << "              maxerror: " << ntv.maxerror << " us" << endl;
    cout << "              esterror: " << ntv.esterror << " us" << endl;
    cout << "              tai     : " << ntv.tai << endl << endl;

    status = adjtime(NULL, &delta);

    cout << "adjtime returned "<< status <<
            ", tv_sec: " << delta.tv_sec <<
            ", tv_usec: " <<  delta.tv_usec << endl << endl;


    struct timex tmx;
    tmx.modes = 0; // Not setting anything
     
    status = ntp_adjtime(&tmx);
    format_timeval(&tmx.time, buf, sizeof(buf));


    cout << "ntp_adjtimex returned    " << status << endl;
    cout << "             offset    : " << tmx.offset << " us" << endl;
    cout << "             freq      : " << tmx.freq << "/65536 ppm" << endl;
    cout << "             maxerror  : " << tmx.maxerror << " us" << endl;
    cout << "             esterror  : " << tmx.esterror << " us" << endl;
    cout << "             status    : " << tmx.status << endl;
    cout << "             constant  : " << tmx.constant << endl;
    cout << "             precision : " << tmx.precision << " us" << endl;
    cout << "             tolerance : " << tmx.tolerance << endl;
    cout << "             time      : " << buf << endl;
    cout << "             tick      : " << tmx.tick << " us" << endl;
    cout << "             ppsfreq   : " << tmx.ppsfreq << "/65536 ppm" << endl;
    cout << "             jitter    : " << tmx.jitter << " us" << endl;
    cout << "             shift     : " << tmx.shift << " s" << endl;
    cout << "             stabil    : " << tmx.stabil << "/65536 ppm (" << endl;
    cout << "             jitcnt    : " << tmx.jitcnt << endl;
    cout << "             calcnt    : " << tmx.calcnt << endl;
    cout << "             errcnt    : " << tmx.errcnt << endl;
    cout << "             stbcnt    : " << tmx.stbcnt << endl;
    cout << "             tai       : " << tmx.tai << " s" << endl;
}

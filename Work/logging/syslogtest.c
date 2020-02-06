#include <syslog.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    openlog("Helge", LOG_PERROR, LOG_LOCAL3);

    syslog(LOG_USER | LOG_ERR, "test log entry fra Helge");

    return 0;
}

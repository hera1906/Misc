#define _XOPEN_SOURCE
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char *cp;
    char *s = "2018 08 23";
    char *format = "%Y %m %d";
    struct tm tm;
    if ((cp = strptime(s, format, &tm)) == NULL)
        printf("strptime returned NULL\n");
    else
    {
        printf("strptime returned NON-NULL, offset from start is %d\n", cp - s);
        printf("Year = %d, month = %d, day = %d\n", tm.tm_year, tm.tm_mon+1, tm.tm_mday);
    }
}

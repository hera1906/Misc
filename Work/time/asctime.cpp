#include <stdio.h>
#include <time.h>
#include <limits.h>

void print(time_t rt) 
{
    printf("time_t %ld\n", (long) rt);
    struct tm * t = gmtime(&rt);
    puts(asctime(t));
}

int main() 
{
    printf("sizeof(time_t): %d\n", sizeof(time_t));
    struct tm tm;

    tm.tm_sec = 1;
    tm.tm_min = 2;
    tm.tm_hour = 3;
    tm.tm_mday = 4;
    tm.tm_mon = 5;

    tm.tm_year = 2019 - 1900;
    char *cp = asctime(&tm);
    time_t t = mktime(&tm);
    printf("year %d: asctime output: %s (time_t: %ld)\n", tm.tm_year + 1900, cp, t);

    tm.tm_year = 2037 - 1900;
    cp = asctime(&tm);
    t = mktime(&tm);
    printf("year %d: asctime output: %s (time_t: %ld)\n", tm.tm_year + 1900, cp, t);

    tm.tm_year = 2038 - 1900;
    cp = asctime(&tm);
    t = mktime(&tm);
    printf("year %d: asctime output: %s (time_t: %ld)\n", tm.tm_year + 1900, cp, t);

    tm.tm_year = 2039 - 1900;
    cp = asctime(&tm);
    t = mktime(&tm);
    printf("year %d: asctime output: %s (time_t: %ld)\n", tm.tm_year + 1900, cp, t);

    tm.tm_year = 2100 - 1900;
    cp = asctime(&tm);
    t = mktime(&tm);
    printf("year %d: asctime output: %s (time_t: %ld)\n", tm.tm_year + 1900, cp, t);

    tm.tm_year = 2200 - 1900;
    cp = asctime(&tm);
    t = mktime(&tm);
    printf("year %d: asctime output: %s (time_t: %ld)\n", tm.tm_year + 1900, cp, t);
}

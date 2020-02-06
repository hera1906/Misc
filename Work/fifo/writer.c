#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define COMMAND_LENGTH 100

int main(int argc, char *argv[])
{
    char command[COMMAND_LENGTH+1];
    int commandLength;
    int fd = -1;
    ssize_t size;
    int maxCount = 1;

    signal(SIGPIPE, SIG_IGN);



    if (argc > 1)
    {
        if (sscanf(argv[1], "%d", &maxCount) != 1)
        {
            printf("Usage: writer [write_count]\n");
            return 99;
        }
    }
    printf("Writing %d messages: ", maxCount);

    for (int count = 0; count < maxCount; count++)
    {
        printf("%d ", count+1); 
        fflush(stdout);

        sprintf(command, "Watchdog: Test=%d\n", count);
        commandLength = strlen(command);

        if (fd < 0)
        {
            if ((fd = open("/tmp/testfifo", O_WRONLY | O_NONBLOCK)) < 0)
            {
                perror("Could not open /tmp/testfifo for writing");
                fd = -1;
            } // if
        } // if

        if (fd >= 0)
        {
            if ((size = write(fd, command, commandLength)) != commandLength)
            {
                if (commandLength < 0)
                    perror("Could not write to fifo");
                else
                    printf("Could not write %d characters to fifo\n", commandLength);
            } // if
        } // if
        sleep(2);
    } // for
    
    if (fd >= 0)
        close(fd);

    printf("\nDone\n");
    return 0;
}

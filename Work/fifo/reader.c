#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define COMMAND_MAXLENGTH 100

int main(int argc, char *argv[])
{
    char ch;
    char command[COMMAND_MAXLENGTH+1];
    int commandLength;
    int fd;
    ssize_t size;
    int count;

    count = 0;

    for (;;)
    {
        printf("Opening fifo\n");
        if ((fd = open("/tmp/testfifo", O_RDONLY)) < 0)
        {
            perror("Could not open /tmp/testfifo");
            return 1;
        } // if

        printf("Reading from fifo...\n");

        commandLength = 0;
        while ((size = read(fd, &ch, 1)) == 1)
        {
            if (ch != '\n')
            {
                if (commandLength < COMMAND_MAXLENGTH-1)
                    command[commandLength++] = ch;
            }
            else
            {
                command[commandLength] = '\0';
                printf("%d: Got command: '%s'\n", count++, command, commandLength);
                commandLength = 0;
            } // if .. else ..
        } // while

        if (size < 0)
        {
            perror("Error reading from fifo");
            close(fd);
            return 2;
        } // if

    } // for (;;)

}

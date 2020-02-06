#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "download.h" 

int main(int argc, char *argv[])
{
    int status;
    if (argc < 2) 
    {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    printf("Downloading %s to page.out\n", argv[1]);
    status = download(argv[1], "page.out", NULL, NULL);
    printf("Status = %d\n", status);

    return status;
}

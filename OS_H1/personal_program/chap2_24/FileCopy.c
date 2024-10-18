#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// strace ./FileCopy

#define MAXLINE 4096

int main()
{

    char input_file[32], output_file[32];
    char *iptr = input_file, *optr = output_file;
    int c;
    char line[MAXLINE];

    printf("Enter source file name: ");
    scanf("%s", iptr);

    int src_fd = open(iptr, O_RDONLY);
    if (src_fd == -1)

    {
        perror("Open src file Error");
        exit(1);
    }

    printf("Enter destination file name: ");
    scanf("%s", optr);
    int des_fd = open(optr, O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (des_fd == -1)

    {
        perror("Open des ile Error");
        exit(1);
    }

    int n = 0;
    while ((n = read(src_fd, line, MAXLINE)) > 0)
    {
        write(des_fd, line, n);
        memset(line, 0, MAXLINE);
    }

    close(src_fd);
    close(des_fd);
    printf("finish\n");

    return 0;
}

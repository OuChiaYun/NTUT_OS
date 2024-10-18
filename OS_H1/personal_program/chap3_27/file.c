#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "string.h"
#include <sys/time.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include <fcntl.h>

#define MAXLINE 4096

int main(int argc, char *argv[])
{

    int pid;
    int fd[2];
    int status;
    char *k;
    int r = 0;
    int n;
    char line[MAXLINE];
    int src_fd = open(argv[1], O_RDONLY);
    int des_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (src_fd == -1)

    {
        perror("Open src file Error");
        exit(1);
    }

    if (des_fd == -1)

    {
        perror("Open des ile Error");
        exit(1);
    }

    if (pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("pip fail\n");
    }
    else if (pid > 0)
    {

        printf("start send fle from parant to child\n");
        close(fd[0]);
        while ((read(src_fd, line, sizeof(line))) > 0)
        {

            r = write(fd[1], line, sizeof(line));
            if (r != sizeof(line))
            {

                perror("pipe write error");
            }
            memset(line, 0, MAXLINE);
        }

        close(src_fd);
        printf("end\n");
    }
    else if (pid == 0)

    {
        wait(&status);
        printf("start child receive file \n");
        close(fd[1]);

        while ((read(fd[0], line, sizeof(line))) > 0)
        {

            r = write(des_fd, line, strlen(line) - 1);

            if (r != strlen(line) - 1)
            {

                perror("write file error");
            }
        }

        close(des_fd);

        printf("end\n");
    }
    return 0;
}

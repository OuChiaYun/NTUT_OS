#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "string.h"
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    int pid;
    struct timeval tv;
    int fd[2];
    long int *f;
    int status;

    f = (long int *)malloc(sizeof(long int *));
    if (f == NULL)
    {
        perror("malloc");
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

        wait(&status);

        close(fd[1]);
        int r = read(fd[0], f, sizeof(f));

        if (r != sizeof(f))
        {

            perror("pipe read error");
        }
        gettimeofday(&tv, NULL);

        printf("\ntotal time (second) :%f\n", (tv.tv_usec - *f) / 1000000.0);
        printf("total time (micro second) :%ld\n", (tv.tv_usec - *f));
    }
    else if (pid == 0)

    {
        printf("start exec \n\n");

        gettimeofday(&tv, NULL);
        *f = tv.tv_usec;

        close(fd[0]);
        int r = write(fd[1], f, sizeof(f));

        if (r != sizeof(f))
        {

            perror("pipe write error");
        }

        int n = execvp(argv[1], &argv[1]);
        if (n == -1)
        {
            perror("execvp error\n");
        }
    }
    return 0;
}


#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "string.h"
#include <sys/time.h>
#include <sys/wait.h>

#define MAXLINE 16

int main(int argc, char *argv[])
{

    int pid;
    int n = 1;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("pip fail\n");
    }
    else if (pid > 0)
    {
        printf("parant wating...\n");
        wait(&status);
        printf("child end.\n");
    }
    else if (pid == 0)

    {
        n = atoi(argv[1]);
        if (n < 1 || argc != 2)
        {
            printf("parameter <0,error\n");
            exit(1);
        }
        else if (n > 1)
        {
            printf("%d->", n);
        }
        else

        {

            printf("%d\n", n);
        }

        while (n > 1)
        {
            if (n % 2 == 0)
            { // for even numbers
                n = n / 2;
                printf("%d", n);
            }
            else
            { // for odd numbers
                n = n * 3 + 1;
                printf("%d", n);
            }
            if (n > 1)
            {
                printf("->");
            }
            else
            {
                printf("\n");
            }
        }
    }
    return 0;
}


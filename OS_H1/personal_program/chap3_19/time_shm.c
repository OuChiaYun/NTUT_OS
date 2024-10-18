#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "string.h"
#include <sys/time.h>
#include <sys/wait.h>

void myfun(int signum)
{
    return;
}

int main(int argc, char *argv[])
{
    int shmid;
    int pid;
    long int *p;
    struct timeval tv;
    int status;

    shmid = shmget(IPC_PRIVATE, 128, IPC_CREAT | 0777);

    if (shmid < 0)
    {
        perror("create shared memory fail\n");
        return -1;
    }

    printf("create shared memory sucess, shmid = %d\n\n", shmid);

    pid = fork();
    if (pid < 0)
    {
        perror("pip fail\n");
    }
    else if (pid > 0)
    {

        p = (long int *)shmat(shmid, NULL, 0);
        if (p == NULL)
        {
            perror("shmat fail\n");
            return -1;
        }

        wait(&status);
        gettimeofday(&tv, NULL);

        printf("\ntotal time (second) :%f\n", (tv.tv_usec - *p) / 1000000.0);
        printf("total time (micro second) :%ld\n", (tv.tv_usec - *p));
    }
    else if (pid == 0)
    {

        p = (long int *)shmat(shmid, NULL, 0);

        if (p == NULL)
        {
            perror("shmat fail\n");
            return -1;
        }

        printf("start exec \n\n");
        gettimeofday(&tv, NULL);
        *p = tv.tv_usec;
        int n = execvp(argv[1], &argv[1]);

        if (n == -1)
        {
            perror("execvp error\n");
        }
    }

    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}


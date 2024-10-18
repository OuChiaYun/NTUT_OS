#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int share_data[100];
sem_t semaphore;

void *runner(void *param);
int main(int argc, char *argv[])
{
    struct Result *thread_result; // declarethe pointer for structure,this is in order to store return value

    pthread_t tid;
    pthread_attr_t attr;

    if (argc == 1)
    {
        printf("no param\n");
        return 0;
    }

    sem_init(&semaphore, 0, 0);
    pthread_attr_init(&attr);
    // thread id,create a pthread
    // function  name
    pthread_create(&tid, &attr, runner, argv[1]); // param pointer

    printf("Fibonacci sequence: ");

    for (int i = 0; i < atoi(argv[1]) + 1; i++)
    {

        sem_wait(&semaphore);
        printf("%d ", share_data[i]);
    }
    printf("\n");

    pthread_join(tid, NULL); // for return value, foce change their tyoe to be void
    sem_destroy(&semaphore);
}

void *runner(void *param)
{
    long s = atoi(param);

    printf("param = %ld\n", s);
    // int the function, to malloc the place to store you value

    share_data[0] = 0;
    sem_post(&semaphore);
    if (s == 0)
    {
        pthread_exit(0);
    }

    share_data[1] = 1;
    sem_post(&semaphore);

    if (s == 1)
    {
        pthread_exit(0);
    }

    for (int i = 2; i < s + 1; i++)
    {
        share_data[i] = share_data[i - 1] + share_data[i - 2];
        sem_post(&semaphore);
    }
    pthread_exit(0);
}
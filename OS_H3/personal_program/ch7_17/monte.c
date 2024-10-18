#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 5
#define NUM_POINTS 10000

int in_cycle = 0;
pthread_mutex_t mutex;

void *runner(void *param);

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], &attr, runner, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("pi = %f\n", 4.0 * in_cycle / (NUM_POINTS * NUM_THREADS));

    pthread_mutex_destroy(&mutex);

    return 0;
}

void *runner(void *param)
{
    srand(time(NULL));

    for (int i = 0; i < NUM_POINTS; i++)
    {
        float x = (double)rand() / RAND_MAX;
        float y = (double)rand() / RAND_MAX;
        float z = x * x + y * y;

        if (z <= 1)
        {
            pthread_mutex_lock(&mutex);
            in_cycle++;
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(0);
}

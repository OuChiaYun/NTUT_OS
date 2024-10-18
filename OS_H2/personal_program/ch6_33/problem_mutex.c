#include <stdio.h>
#include <pthread.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int decrease_count(int count)
{

    pthread_mutex_lock(&mutex);
    if (available_resources < count)
    {
        printf("Decreased resource. Available resources: %d\n", available_resources);

        pthread_mutex_unlock(&mutex);

        return -1;
    }
    else
    {
        available_resources -= count;
        printf("Decreased resource. Available resources: %d\n", available_resources);

        pthread_mutex_unlock(&mutex);
        return 0;
    }
}
int increase_count(int count)
{
    pthread_mutex_lock(&mutex);
    available_resources += count;
    printf("Increased resource. Available resources: %d\n", available_resources);
    pthread_mutex_unlock(&mutex);
    return 0;
}

void *decrease_resource(void *arg)
{
    for (int i = 0; i < 5; ++i)
    {
        decrease_count(1);
    }
    pthread_exit(NULL);
}

void *increase_resource(void *arg)
{
    for (int i = 0; i < 5; ++i)
    {
        increase_count(1);
        // printf("Increased resource. Available resources: %d\n", available_resources);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_dec, thread_inc;

    pthread_create(&thread_dec, NULL, decrease_resource, NULL);

    pthread_create(&thread_inc, NULL, increase_resource, NULL);

    pthread_join(thread_dec, NULL);
    pthread_join(thread_inc, NULL);

    return 0;
}

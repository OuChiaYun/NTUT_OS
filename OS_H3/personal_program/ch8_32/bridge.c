#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t bridge; // 橋資源
void enterbridge(char name)
{

    sem_wait(&bridge);
    printf("-----------[start]-------------\n");
    if (name == 'n')
    {
        printf("North farmer start passing\n");
        return;
    }

    if (name == 's')
    {

        printf("South farmer start passing\n");
        return;
    }
}

void exitbridge(char name)
{

    if (name == 'n')
    {
        printf("North farmer finish passing\n");
    }

    if (name == 's')
    {
        printf("South farmer finish passing\n");
    }

    printf("-----------[end]---------------\n\n");
    sem_post(&bridge);
}

void *northbound(void *arg)
{

    enterbridge('n');
    /////////////////////
    int sleep_time = rand() % 5;
    printf("North farmer passing time %d\n", sleep_time);
    sleep(sleep_time); // walking
    /////////////////////
    exitbridge('n');
}
void *southbound(void *arg)
{

    enterbridge('s');
    /////////////////////
    int sleep_time = rand() % 5;
    printf("South farmer passing time %d\n", sleep_time);
    sleep(sleep_time); // walking
    /////////////////////
    exitbridge('s');
}

int main()
{
    sem_init(&bridge, 0, 1);
    int farmers = 10;

    pthread_t north_farmer_threads[farmers], south_farmer_threads[farmers];

    for (int i = 0; i < farmers; i++)
    {
        pthread_t north_thread, south_thread;
        pthread_create(&north_thread, NULL, northbound, NULL);
        pthread_create(&south_thread, NULL, southbound, NULL);
        north_farmer_threads[i] = north_thread;
        south_farmer_threads[i] = south_thread;
    }

    for (int i = 0; i < farmers; i++)
    {
        pthread_join(north_farmer_threads[i], NULL);
        pthread_join(south_farmer_threads[i], NULL);
    }
    sem_destroy(&bridge);
    return 0;
}
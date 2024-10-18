#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int in_cycle = 0;

void *runner(void *param);

int main(int argc, char *argv[])
{
    struct Result *thread_result;

    pthread_t tid;
    pthread_attr_t attr;

    if (argc == 1)
    {
        printf("no param\n");
        return 0;
    }
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);

    printf("pi = %f\n", 4.0 * in_cycle / atoi(argv[1]));
}

void *runner(void *param)
{
    long s = atoi(param);

    printf("param = %ld\n", s);
    srand(time(NULL));

    for (int i = 0; i < s; i++)
    {
        float x = (double)rand() / RAND_MAX;
        // printf("x = %f\n", x);
        float y = (double)rand() / RAND_MAX;
        // printf("y = %f\n", y);

        float z = x * x + y * y;

        if (z <= 1)
        {
            in_cycle++;
        }
    }

    pthread_exit(0);
}
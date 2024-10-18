#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct Result
{
    int *array;
    int length;
};
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

    pthread_attr_init(&attr);

    // thread id,create a pthread
    // function  name
    pthread_create(&tid, &attr, runner, argv[1]); // param pointer
    pthread_join(tid, (void **)&thread_result);   // for return value, foce change their tyoe to be void

    printf("Fibonacci sequence: ");

    for (int i = 0; i < atoi(argv[1]) + 1; i++)
    {
        printf("%d ", thread_result->array[i]);
    }
    printf("\n");

    free(thread_result->array); // because you malloc, you need to free
    free(thread_result);        // free the stucture
}

void *runner(void *param)
{
    long s = atoi(param);

    printf("param = %ld\n", s);

    struct Result *result = (struct Result *)malloc(sizeof(struct Result)); // int the function, to malloc the place to store you value

    result->length = s + 1;
    result->array = (int *)malloc(s * sizeof(int));
    result->array[0] = 0;

    if (s == 0)
    {
        pthread_exit(result);
    }

    result->array[1] = 1;

    if (s == 1)
    {
        pthread_exit(result);
    }

    for (int i = 2; i < s + 1; i++)
    {
        result->array[i] = result->array[i - 1] + result->array[i - 2];
    }

    pthread_exit(result);
}
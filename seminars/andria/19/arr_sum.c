#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STEP_SIZE 1000
#define ARR_SIZE 1000000

static int sum = 0;
static pthread_mutex_t lock;

typedef struct
{
    int *arr;
    int index;
} thread_args_t;

void *calculate_sum(void *args)
{
    int *arr = ((thread_args_t *)args)->arr;
    int thread_index = ((thread_args_t *)args)->index;

    int *local_sum = malloc(sizeof(int));

    printf("Thread %d started\n", thread_index);

    for (int i = thread_index * STEP_SIZE; (i < (thread_index + 1) * STEP_SIZE) && i < ARR_SIZE; i++)
    {
        *local_sum += arr[i];
    }

    // pthread_mutex_lock(&lock);
    // sum += local_sum;
    // pthread_mutex_unlock(&lock);

    printf("Thread %d finished\n", thread_index);

    return local_sum;
}

int main() {
    int arr[ARR_SIZE];

    for (int i = 0; i < ARR_SIZE; i++) arr[i] = i;

    int num_threads = (ARR_SIZE / STEP_SIZE) + 1;
    pthread_t threads[num_threads];
    thread_args_t args[num_threads];

    pthread_mutex_init(&lock, 0);

    clock_t start = clock();

    for (int i = 0 ; i < num_threads; i++)
    {
        args[i].arr = arr;
        args[i].index = i;
        pthread_create(&threads[i], 0, calculate_sum, args + i);
    }

    for (int i = 0; i < num_threads; i++) {
        void *local_sum;
        pthread_join(threads[i], &local_sum);
        sum += *((int *)local_sum);

        free(local_sum);
    }

    clock_t end = clock();
    double total = (double)(end - start) / CLOCKS_PER_SEC;

    printf("sum: %d;  time in second: %f\n", sum, total);

    pthread_mutex_destroy(&lock);
    return 0;
}
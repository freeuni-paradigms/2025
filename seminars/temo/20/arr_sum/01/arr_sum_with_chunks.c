#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define ARR_SIZE 100000
#define MAX_NUM 1000

void generateArray(int *arr)
{
    int sum = 0;
    for (int i = 0; i < ARR_SIZE; i++)
    {
        arr[i] = rand() % MAX_NUM;
        sum += arr[i];
    }
    printf("Sum of array is %d\n", sum);
}

typedef struct {
  int *arr;
  int start_index;
  int *sum;
  pthread_mutex_t* lock;
} Args;


void* calculate_sum(void *a){
  Args *args = (Args *)a;

  int last_index = args->start_index + (ARR_SIZE / NUM_THREADS) < ARR_SIZE ? args->start_index + (ARR_SIZE / NUM_THREADS) : ARR_SIZE - 1;

  int sum = 0;

  for (int i = args->start_index; i < args->start_index + ARR_SIZE / NUM_THREADS; i++) {
    sum += args->arr[i];
  }
 
  pthread_mutex_lock(args->lock);
  *args->sum += sum;
  pthread_mutex_unlock(args->lock);
  // LOCK
  // sum += 20;
  // UNLOCK

  // lw x10, sum
  // addi x10, 20
  // sw x10, sum
}


int main(){
  int sum = 0;
  int arr[ARR_SIZE];
  generateArray(arr);
  
  pthread_t threads[NUM_THREADS];
  Args args[NUM_THREADS];
    
  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    args[i].arr = arr;
    args[i].start_index = i * (ARR_SIZE / NUM_THREADS);
    args[i].sum = &sum;
    args[i].lock = &lock;
    pthread_create(&threads[i], NULL, calculate_sum, &args[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);  
  }
  
  printf("%d\n", sum);
  return 0;
}

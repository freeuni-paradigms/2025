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
  int *index;
  int *sum;
  pthread_mutex_t* lock;
} Args;


void* calculate_sum(void *a){
  Args *args = (Args *)a;

  int _rand = rand();
  if (_rand % 4) {
    printf("%d ZZZ\n", _rand);
    sleep(120);
  }

  while (true) {
    pthread_mutex_lock(args->lock);
    int index = *args->index;
    if (index >= ARR_SIZE) {
      pthread_mutex_unlock(args->lock);
      break;
    }
    *args->sum += args->arr[index];
    (*args->index)++;
    pthread_mutex_unlock(args->lock);
  }
}


int main(){
  srand(time(NULL));
  int sum = 0;
  int index = 0;
  int arr[ARR_SIZE];
  generateArray(arr);
  
  pthread_t threads[NUM_THREADS];
  Args args[NUM_THREADS];
    
  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    args[i].arr = arr;
    args[i].index = &index;
    args[i].sum = &sum;
    args[i].lock = &lock;
    pthread_create(&threads[i], NULL, calculate_sum, &args[i]);
  }

  sleep(1);

  printf("%d\n", sum);
  return 0;
}

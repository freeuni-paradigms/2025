#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define LAST_INDEX 1000

typedef struct Args {
  pthread_mutex_t *odd_lock;
  pthread_mutex_t *even_lock;
} Args;

void* print_even(void *a) {
  Args *args = (Args *) a;
  for (int i = 0; i < LAST_INDEX; i+=2) {
    pthread_mutex_lock(args->even_lock);
    printf("%d ", i);
    pthread_mutex_unlock(args->odd_lock);
  }
}

void* print_odd(void *a) {
  Args *args = (Args *) a;
  for (int i = 1; i < LAST_INDEX; i+=2) {
    pthread_mutex_lock(args->odd_lock);
    printf("%d ", i);
    pthread_mutex_unlock(args->even_lock);
  }
}

int main() {
  pthread_t t1;
  pthread_t t2;
  
  pthread_mutex_t odd_lock;
  pthread_mutex_t even_lock;
  pthread_mutex_init(&odd_lock, NULL);
  pthread_mutex_init(&even_lock, NULL);

  Args args;
  args.odd_lock = &odd_lock;
  args.even_lock = &even_lock;

  pthread_mutex_lock(&odd_lock);

  pthread_create(&t1, NULL, print_even, &args);
  pthread_create(&t2, NULL, print_odd, &args);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("\n");
}

#include <pthread.h>
#include "sem_using_mutex.h"
#include <stdio.h>

#define MAX_VALUE 100

typedef struct Args {
  semT *sem_odd;
  semT *sem_even;
} Args;

void* print_evens(void *a) {
  Args *args = (Args *)a;

  for (int i = 0; i < MAX_VALUE; i+=2) {
    semWait(args->sem_even);
    printf("%d  ", i);
    semPost(args->sem_odd);
  }
}

void* print_odds(void *a) {
  Args *args = (Args *)a;

  for (int i = 1; i < MAX_VALUE; i+=2) {
    semWait(args->sem_odd);
    printf("%d  ", i);
    semPost(args->sem_even);
  }
}

int main() {
   semT sem_odd;
   semT sem_even;
   
   semInit(&sem_odd, 0);
   semInit(&sem_even, 1);

   pthread_t thread_even;
   pthread_t thread_odd;

   Args args;
   args.sem_odd = &sem_odd;
   args.sem_even = &sem_even;

   pthread_create(&thread_even, NULL, print_evens, &args);
   pthread_create(&thread_odd, NULL, print_odds, &args);

   pthread_join(thread_odd, NULL);

   printf("\n");
}


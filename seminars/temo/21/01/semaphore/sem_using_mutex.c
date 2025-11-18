#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sem_using_mutex.h"

//  typedef struct
//  {
//      int counter;
//      pthread_mutex_t *mutex;
//      pthread_cond_t *cond;
//  } semT;
// 

void semInit(semT *s, int value) {
  s->counter = value;
  pthread_mutex_t *mutex = malloc(sizeof(pthead_mutex_t));
  pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
  pthread_mutex_init(mutex, NULL);
  pthread_cond_init(cond, NULL);
  s->mutex = mutex;
  s->cond = cond;
}

void semPost(semT *s) {
  pthread_mutex_lock(s->mutex);
  s->counter += 1;
  if (s->counter == 1) {
    pthread_cond_signal(s->cond);
  }
  pthread_mutex_unlock(s->mutex);
}

void semWait(semT *s) {
  pthread_mutex_lock(s->mutex);
  while (s->counter == 0) {
    pthread_cond_wait(s->cond, s->mutex);
  }
  s->counter -= 1;
  pthread_mutex_unlock(s->mutex);
}


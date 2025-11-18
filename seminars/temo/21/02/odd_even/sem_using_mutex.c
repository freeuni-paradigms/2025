#include "sem_using_mutex.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//typedef struct
//{
//    int counter;
//    pthread_mutex_t *mutex;
//    pthread_cond_t *cond;
//} semT;

void semInit(semT *s, int value) {
  s->counter = value;
  s->mutex = malloc(sizeof(pthread_mutex_t));
  s->cond = malloc(sizeof(pthread_cond_t));
  pthread_mutex_init(s->mutex, NULL);
  pthread_cond_init(s->cond, NULL);
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


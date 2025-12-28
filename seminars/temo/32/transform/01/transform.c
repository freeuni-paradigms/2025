#include "transform.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#define max(a, b) (a > b ? a : b)

typedef struct GrowData {
  int *heights;
  int n;
  int i;
  int *count;
  int *iteration;
  bool *finished;
  pthread_mutex_t *lock;
  pthread_cond_t *cond;
} GrowData;

void* grow(void *data) {
  GrowData *growData = (GrowData*)data;

  while (1) {
    int newVal = growData->heights[growData->i];
    if (growData->i != 0) {
      newVal = max(newVal, growData->heights[growData->i - 1]);
    }
    if (growData->i < growData->n - 1) {
      newVal = max(newVal, growData->heights[growData->i + 1]);
    }
    if (newVal != growData->heights[growData->i]) {
      *growData->finished = false;
    }
    
    pthread_mutex_lock(growData->lock);
    *growData->count += 1;
    
    if (*growData->count == growData->n) {
      // broadcast
      *growData->count = 0;
      *growData->iteration += 1;
      pthread_cond_broadcast(growData->cond);
    } else {
      // wait
      pthread_cond_wait(growData->cond, growData->lock);
    }
    // unlock
    pthread_mutex_unlock(growData->lock);

    if (*growData->finished) {
      break;
    }
    // write new data

    growData->heights[growData->i] = newVal;

    pthread_mutex_lock(growData->lock);
    *growData->count += 1;

    if (*growData->count == growData->n) {
      // broadcast
      *growData->count = 0;
      *growData->finished = true;
      pthread_cond_broadcast(growData->cond);
    } else {
      // wait
      pthread_cond_wait(growData->cond, growData->lock);
    }
    // unlock
    pthread_mutex_unlock(growData->lock);
  }
}

int Transform(int* heights, int n) {
  pthread_t grow_threads[n];
  GrowData growData[n];
  int count = 0;
  int iteration = -1;
  bool finished = true;
  pthread_mutex_t lock;
  pthread_cond_t cond;

  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);

  for(int i = 0; i < n; i++) {
    growData[i].heights = heights;
    growData[i].n = n;
    growData[i].i = i;
    growData[i].finished = &finished;
    growData[i].count = &count;
    growData[i].iteration = &iteration;
    growData[i].lock = &lock;
    growData[i].cond = &cond;

    pthread_create(&grow_threads[i], NULL, grow, &growData[i]);
  } 
  for (int i = 0; i< n; i++) {
    pthread_join(grow_threads[i], NULL);
  }
  return iteration;
}

#include "transform.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#define max(a, b) (a > b ? a : b)

typedef struct Grow {
  int *heights;
  int n;
  int *count;
  int *generation;
  bool *finished;
  int i;
  pthread_cond_t *cond;
  pthread_mutex_t *lock;
} Grow;

void* grow(void* data) {
  Grow *g = (Grow *) data;

  while (1) {
    int height = g->heights[g->i];
    int left = 0;
    int right = 0;
    if (g->i > 0) {
      left = g->heights[g->i - 1];
    }
    if (g->i < g->n - 1) {
      right = g->heights[g->i + 1];
    }
    height = max(height, left);
    height = max(height, right);

    if (height != g->heights[g->i]) {
      *g->finished = false;
    }

    pthread_mutex_lock(g->lock);
    int gen = *g->generation;
    *g->count -= 1;

    if (*g->count > 0) {
      while (gen == *g->generation) {
        pthread_cond_wait(g->cond, g->lock);
      }
    } else {
      *g->count = g->n;
      *g->generation += 1;
      pthread_cond_broadcast(g->cond);
    }
    pthread_mutex_unlock(g->lock);

    if (*g->finished) {
      break;
    }

    g->heights[g->i] = height;

    pthread_mutex_lock(g->lock);
    gen = *g->generation;
    *g->count -= 1;
   

    if (*g->count > 0) {
      while (gen == *g->generation) {
        pthread_cond_wait(g->cond, g->lock);
      }
    } else {
      *g->count = g->n;
      *g->generation += 1;
      /**! aq unda gavatrueot g->finished **/
      *g->finished = true;
      pthread_cond_broadcast(g->cond);
    }
    pthread_mutex_unlock(g->lock);
  }
}

int Transform(int* heights, int n) {
  pthread_t threads[n];
  Grow g[n];

  pthread_mutex_t l;
  pthread_cond_t c;

  pthread_mutex_init(&l, NULL);
  pthread_cond_init(&c, NULL);
  
  int count = n;
  int generation = 0; 
  bool finished = true;

  for(int i = 0; i < n; i++) {
    g[i].heights = heights;
    g[i].n = n;
    g[i].count = &count;
    g[i].generation = &generation;
    g[i].i = i;
    g[i].finished = &finished;
    g[i].cond = &c;
    g[i].lock = &l;
    pthread_create(&threads[i], NULL, grow, &g[i]);
  }
  for (int i = 0; i < n; i++) {
    pthread_join(threads[i], NULL);
  }
  return generation / 2;
}

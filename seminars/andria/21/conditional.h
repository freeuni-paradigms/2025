#ifndef __CONDITIONAL_H__
#define __CONDITIONAL_H__

#include <pthread.h>

typedef struct
{
    pthread_mutex_t sync_lock;
} my_cond_t;

void cond_init(my_cond_t *this);
void cond_wait(my_cond_t *this, pthread_mutex_t *lock);
void cond_signal(my_cond_t *this);
void cond_destroy(my_cond_t *this);

#endif  // __CONDITIONAL_H__

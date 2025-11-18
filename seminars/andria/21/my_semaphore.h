#ifndef __MY_SEMAPHORE_H__
#define __MY_SEMAPHORE_H__

#include <pthread.h>

typedef struct
{
    int count;
    pthread_mutex_t data_lock; //, sync_lock;
    pthread_cond_t cond;
} my_sem_t;

void sem_init(my_sem_t *this, int value);
void sem_wait(my_sem_t *this);
void sem_post(my_sem_t *this);
void sem_destroy(my_sem_t *this);

#endif  //__MY_SEMAPHORE_H__

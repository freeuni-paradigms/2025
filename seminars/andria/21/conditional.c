#include "conditional.h"

#define LOCK(mut) (pthread_mutex_lock(mut))
#define UNLOCK(mut) (pthread_mutex_unlock(mut))

/*
    DISCLAMER !!!!!!

    simple implementation without cond_broadcast
    cond_broadcast adds complexsity
*/

void cond_init(my_cond_t *this)
{
    pthread_mutex_init(&this->sync_lock, NULL);
}

void cond_wait(my_cond_t *this, pthread_mutex_t *lock)
{
    UNLOCK(lock);
    LOCK(&this->sync_lock);
    LOCK(lock);
}

void cond_signal(my_cond_t *this)
{
    UNLOCK(&this->sync_lock);
}

void cond_destroy(my_cond_t *this)
{
    pthread_mutex_destroy(&this->sync_lock);
}


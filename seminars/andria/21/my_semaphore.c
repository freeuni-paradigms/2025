#include "my_semaphore.h"

#define LOCK(mut) (pthread_mutex_lock(mut))
#define UNLOCK(mut) (pthread_mutex_unlock(mut))

void sem_init(my_sem_t *this, int value)
{
    this->count = value;
    // pthread_mutex_init(&this->sync_lock, NULL);
    pthread_mutex_init(&this->data_lock, NULL);

    pthread_cond_init(&this->cond, NULL);

    // LOCK(&this->sync_lock);
}

void sem_wait(my_sem_t *this)
{
    LOCK(&this->data_lock);

    while (this->count == 0)
        pthread_cond_wait(&this->cond, &this->data_lock);

    // {
    //     UNLOCK(&this->data_lock);
    //     LOCK(&this->sync_lock);
    //     LOCK(&this->data_lock);
    // }

    this->count--;

    UNLOCK(&this->data_lock);
}

void sem_post(my_sem_t *this)
{
    LOCK(&this->data_lock);

    this->count++;
    // UNLOCK(&this->sync_lock);
    pthread_cond_signal(&this->cond);

    UNLOCK(&this->data_lock);
}

void sem_destroy(my_sem_t *this)
{
    // pthread_mutex_destroy(&this->sync_lock);
    pthread_mutex_destroy(&this->data_lock);
    pthread_cond_destroy(&this->cond);
}


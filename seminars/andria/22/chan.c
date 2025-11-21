#include "chan.h"

#include <stdlib.h>

// typedef struct
// {  
//     int buffer_size;
//     Queue *queue;

//     sem_t read, write;
// } chan_t; // (same as blocking queue)

void chanInit(chan_t *chan, int elem_size, int buffer_size)
{
    chan->is_buffered = buffer_size != 0;

    chan->queue = malloc(sizeof(Queue));
    queueInit(chan->queue, elem_size);

    pthread_mutex_init(&chan->lock, NULL);
    sem_init(&chan->read, 0, 0);
    sem_init(&chan->write, 0, buffer_size);
}

void chanSend(chan_t *chan, void *elem)
{
    sem_wait(&chan->write);

    pthread_mutex_lock(&chan->lock);
    enQueue(chan->queue, elem);
    pthread_mutex_unlock(&chan->lock);

    sem_post(&chan->read);
}

void chanRecv(chan_t *chan, void *elem)
{
    if (!chan->is_buffered) sem_post(&chan->write);
    sem_wait(&chan->read);

    pthread_mutex_lock(&chan->lock);
    deQueue(chan->queue, elem);
    pthread_mutex_unlock(&chan->lock);

    if (chan->is_buffered) sem_post(&chan->write);
}

void chanDestroy(chan_t *chan)
{
    pthread_mutex_destroy(&chan->lock);
    sem_destroy(&chan->read);
    sem_destroy(&chan->write);

    queueDestroy(chan->queue);
    free(chan->queue);
}
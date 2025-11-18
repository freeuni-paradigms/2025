#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int counter;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
} semT;

void semInit(semT *s, int value);

void semPost(semT *s);

void semWait(semT *s);
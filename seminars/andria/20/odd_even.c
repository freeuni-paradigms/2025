#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define PRINT_MAX 100

typedef pthread_mutex_t mut_t;

typedef struct
{
    // mut_t *odd_lock;
    // mut_t *even_lock;
    sem_t *odd_sem;
    sem_t *even_sem;
} thread_args_t;

void *odd_fn(void *args)
{
    // mut_t *odd_lock = ((thread_args_t *)args)->odd_lock;
    // mut_t *even_lock = ((thread_args_t *)args)->even_lock;
    sem_t *odd_sem = ((thread_args_t *)args)->odd_sem;
    sem_t *even_sem = ((thread_args_t *)args)->even_sem;

    for (int i = 1; i <= PRINT_MAX; i += 2)
    {
        // pthread_mutex_lock(odd_lock);
        sem_wait(odd_sem);

        printf("odd: %d\n", i);

        // pthread_mutex_unlock(even_lock);
        sem_post(even_sem);
    }

    return 0;
}

void *even_fn(void *args)
{
    // mut_t *odd_lock = ((thread_args_t *)args)->odd_lock;
    // mut_t *even_lock = ((thread_args_t *)args)->even_lock;
    sem_t *odd_sem = ((thread_args_t *)args)->odd_sem;
    sem_t *even_sem = ((thread_args_t *)args)->even_sem;

    for (int i = 2; i <= PRINT_MAX; i += 2)
    {
        // pthread_mutex_lock(even_lock);
        sem_wait(even_sem);

        printf("even: %d\n", i);

        // pthread_mutex_unlock(odd_lock);
        sem_post(odd_sem);
    }

    return 0;
}

int main()
{
    pthread_t odd_thread, even_thread;
    // mut_t odd_lock, even_lock;
    sem_t odd_sem, even_sem; // *odd_sem, *even_sem for MacOS

    // pthread_mutex_init(&odd_lock, NULL);
    // pthread_mutex_init(&even_lock, NULL);
    sem_init(&odd_sem, 0, 1);
    sem_init(&even_sem, 0, 0);

    // ONLY ON MAC: (sem_init is depricated on Mac OS)
    // odd_sem = sem_open("/odd_sem", O_CREAT, 0644, 1);
    // even_sem = sem_open("/even_sem", O_CREAT, 0644, 0);

    thread_args_t args;
    // args.odd_lock = &odd_lock;
    // args.even_lock = &even_lock;
    args.odd_sem = &odd_sem;
    args.even_sem = &even_sem;

    // pthread_mutex_lock(&even_lock); // make even_lock value 0 like on semaphores

    pthread_create(&odd_thread, NULL, odd_fn, &args);
    pthread_create(&even_thread, NULL, even_fn, &args);

    pthread_join(odd_thread, NULL);
    pthread_join(even_thread, NULL);

    // pthread_mutex_destroy(&odd_lock);
    // pthread_mutex_destroy(&even_lock);
    sem_destroy(&even_sem);
    sem_destroy(&odd_sem);
    
    // ONLY ON MAC: (sem_init is depricated on Mac OS)
    // sem_close(even_sem);
    // sem_close(odd_sem);

    return 0;
}

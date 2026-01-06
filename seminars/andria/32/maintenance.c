#include "maintenance.h"

#include "supervisor.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define LOCK(lock) (pthread_mutex_lock(lock))
#define UNLOCK(lock) (pthread_mutex_unlock(lock))

typedef struct
{
    int num_tables, hw_free_size, sw_free_size;
    int *hw_free_stack;
    int *sw_free_stack;

    pthread_mutex_t shared_lock;
    pthread_cond_t cond;
} SharedData;

typedef struct 
{
    SharedData *shared;
    int id;

    int *num_workers_left;
    pthread_mutex_t *internal_lock;
} Args;

void *hw_worker(void *args)
{
    Args *data = ((Args *)args);
    SharedData *shared = data->shared;

    HardwareWorkerEnterRoom(data->id);

    while (true)
    {
        LOCK(&shared->shared_lock);
        if (shared->hw_free_size == 0) {
            UNLOCK(&shared->shared_lock);
            break;
        }

        int table_index = --shared->hw_free_size;
        int table_id = shared->hw_free_stack[table_index];
        UNLOCK(&shared->shared_lock);

        HardwareWorkerStartSettingUpComputer(data->id, table_id);
        HardwareWorkerFinishedSettingUpComputer(data->id, table_id);

        LOCK(&shared->shared_lock);
        int sw_table_index = shared->sw_free_size++;
        shared->sw_free_stack[sw_table_index] = table_id;
        
        pthread_cond_signal(&shared->cond);
        UNLOCK(&shared->shared_lock);
    }
    pthread_cond_broadcast(&shared->cond);

    LOCK(data->internal_lock);
    if (*data->num_workers_left == 1)
        AllComputerHardwareIsSetUp(data->id);

    HardwareWorkerLeaveRoom(data->id);
    (*data->num_workers_left)--;
    UNLOCK(data->internal_lock);

    return NULL;
}

void *sw_worker(void *args)
{
    Args *data = ((Args *)args);
    SharedData *shared = data->shared;

    SoftwareWorkerEnterRoom(data->id);

    while (true) 
    {
        LOCK(&shared->shared_lock);
        while (shared->hw_free_size != 0 && 
               shared->sw_free_size == 0) 
        {
            pthread_cond_wait(&shared->cond, &shared->shared_lock);
        }

        if (shared->hw_free_size == 0 && 
               shared->sw_free_size == 0)
        {
            UNLOCK(&shared->shared_lock);
            break;
        }

        int computer_index = --shared->sw_free_size;
        int computer_id = shared->sw_free_stack[computer_index];
        UNLOCK(&shared->shared_lock);

        SoftwareWorkerStartInstallingSoftware(data->id, computer_id);
        SoftwareWorkerFinishedInstallingSoftware(data->id, computer_id);
    }

    LOCK(data->internal_lock);
    if (*data->num_workers_left == 1)
        AllComputerSoftwareIsInstalled(data->id);

    SoftwareWorkerLeaveRoom(data->id);
    (*data->num_workers_left)--;
    UNLOCK(data->internal_lock);

    return NULL;
}

void SetUpServerRoom(int num_tables, int hardware_team_size, int software_team_size) 
{
    pthread_t hw_workers[hardware_team_size];
    pthread_t sw_workers[software_team_size];

    Args hw_args[hardware_team_size];
    Args sw_args[software_team_size];

    // init shared data
    SharedData shared;
    shared.num_tables = num_tables;
    shared.hw_free_size = num_tables;
    shared.sw_free_size = 0;

    int hw_free_stack[num_tables];
    int sw_free_stack[num_tables];

    shared.hw_free_stack = hw_free_stack;
    shared.sw_free_stack = sw_free_stack;

    pthread_mutex_init(&shared.shared_lock, NULL);
    pthread_cond_init(&shared.cond, NULL);

    // init hw_free_stack
    for (int i = 0; i < num_tables; i++)
        hw_free_stack[i] = i;


    pthread_mutex_t hw_internal_lock;
    pthread_mutex_init(&hw_internal_lock, NULL);
    int hw_size = hardware_team_size;
    for (int i = 0; i < hardware_team_size; i++) {
        Args *args = &hw_args[i];
        args->id = i;
        args->shared = &shared;
        args->num_workers_left = &hw_size;
        args->internal_lock = &hw_internal_lock;

        pthread_create(&hw_workers[i], NULL, hw_worker, args);
    }

    pthread_mutex_t sw_internal_lock;
    pthread_mutex_init(&sw_internal_lock, NULL);
    int sw_size = software_team_size;
    for (int i = 0; i < software_team_size; i++) {
        Args *args = &sw_args[i];
        args->id = i;
        args->shared = &shared;
        args->num_workers_left = &sw_size;
        args->internal_lock = &sw_internal_lock;

        pthread_create(&sw_workers[i], NULL, sw_worker, args);
    }

    
    for (int i = 0; i < hardware_team_size; i++) {
        pthread_join(hw_workers[i], NULL);
    }

    for (int i = 0; i < software_team_size; i++) {
        pthread_join(sw_workers[i], NULL);
    }
}

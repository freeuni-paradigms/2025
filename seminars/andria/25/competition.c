#include "competition.h"
#include "robot.h"

#include <stdlib.h>


#define LOCK(mut) (pthread_mutex_lock(&mut))
#define UNLOCK(mut) (pthread_mutex_unlock(&mut))

typedef struct
{
    Competition *comp;
    const Robot *robot1, *robot2;
} ArenaArgs;


void *Arena(void *args) {
    ArenaArgs *arena_args = args;
    Competition *comp = arena_args->comp; 

    bool result = RobotFightWith(arena_args->robot1, arena_args->robot2);
    const Robot *winner = result ? arena_args->robot1 : arena_args->robot2;

    LOCK(comp->lock);
    comp->robots[comp->arr_len++] = winner;
    comp->active_robots_count--;
    UNLOCK(comp->lock);

    pthread_cond_signal(&comp->cond);

    free(arena_args);
    return NULL;
}

void *FightManager(void *args) {
    Competition *comp = args;

    while (true) {
        // check if we need to continue searching
        LOCK(comp->lock);

        // check for arr size
        while ((comp->arr_len < 2) && 
               (!comp->is_stopping || comp->active_robots_count >= 2)) 
        {
            pthread_cond_wait(&comp->cond, &comp->lock);
        }

        if (comp->is_stopping && comp->active_robots_count < 2) {
            UNLOCK(comp->lock);
            break;
        }

        ArenaArgs *args = malloc(sizeof(ArenaArgs));
        args->comp = comp;
        args->robot1 = comp->robots[--comp->arr_len];
        args->robot2 = comp->robots[--comp->arr_len];

        UNLOCK(comp->lock);

        // run fight in another thread
        pthread_t arena_thread;
        pthread_create(&arena_thread, NULL, Arena, args);
        pthread_detach(arena_thread);
    }
    
    return NULL;
}

void CompetitionInit(Competition* comp) {
    comp->arr_len = 0;
    comp->active_robots_count = 0;

    comp->is_stopping = false;
    pthread_mutex_init(&comp->lock, NULL);
    pthread_cond_init(&comp->cond, NULL);
}

void CompetitionStart(Competition* comp) {
    pthread_create(&comp->manager_thread, NULL, FightManager, comp);
}

const Robot* CompetitionStop(Competition* comp) {  
    LOCK(comp->lock);
    comp->is_stopping = true;
    UNLOCK(comp->lock);

    pthread_join(comp->manager_thread, NULL);
    const Robot *winner = comp->robots[0];

    pthread_mutex_destroy(&comp->lock);
    pthread_cond_destroy(&comp->cond);

    return winner;
}

bool CompetitionAddParticipant(Competition* comp, const Robot* robot) {
    LOCK(comp->lock);

    if (comp->is_stopping) {
        UNLOCK(comp->lock);
        return false;
    }

    comp->robots[comp->arr_len++] = robot;
    comp->active_robots_count++;

    UNLOCK(comp->lock);

    pthread_cond_signal(&comp->cond);
    return true;
}

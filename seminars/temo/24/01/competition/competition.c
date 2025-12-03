#include "competition.h"

#include <stdlib.h>

#include "robot.h"

#define COMPETITION_FINISHED(comp) (comp->competition_stop && comp->robots_count == 1 && comp->robots_in_fight == 0) 

void CompetitionInit(Competition* comp) {
  comp->competition_stop = false;
  comp->robots_count = 0;
  comp->robots_in_fight = 0;
  pthread_mutex_init(&comp->lock, NULL);
  pthread_mutex_init(&comp->array, NULL);
  pthread_mutex_init(&comp->wait_competition, NULL);
  pthread_mutex_lock(&comp->wait_competition);

  pthread_cond_init(&comp->cond_wait_robot, NULL);
}

typedef struct FightArgs {
  Robot *robot1;
  Robot *robot2;
  Competition *comp;
} FightArgs;

void *Fight(void *data) {
  FightArgs *fightArgs = (FightArgs *) data;
  Competition *comp = fightArgs->comp;

  bool result = RobotFightWith(fightArgs->robot1, fightArgs->robot2);

  Robot *winner = fightArgs->robot2;
  if (result) {
    winner = fightArgs->robot1;
  }

  pthread_mutex_lock(&comp->array);
  comp->robots[comp->robots_count] = winner;
  comp->robots_count += 1;
  comp->robots_in_fight -= 2;
  // SIGNAL WHEN competition is finished !
  if (comp->robots_count == 2 || COMPETITION_FINISHED(comp)) {
    pthread_cond_signal(&comp->cond_wait_robot);
  }
  pthread_mutex_unlock(&comp->array);

  free(data);
}

void *Management(void* data) {
  Competition *comp = (Competition *) data;
  
  while (true) {
    pthread_mutex_lock(&comp->lock);
    pthread_mutex_lock(&comp->array);
    if (COMPETITION_FINISHED(comp)) {
      pthread_mutex_unlock(&comp->array);
      pthread_mutex_unlock(&comp->lock);
      break;
    }
    pthread_mutex_unlock(&comp->array);
    pthread_mutex_unlock(&comp->lock);
      
    pthread_mutex_lock(&comp->array);
    if (comp->robots_count < 2) {
      pthread_cond_wait(&comp->cond_wait_robot, &comp->array);
      pthread_mutex_unlock(&comp->array);
    } else {
      Robot *r1 = comp->robots[comp->robots_count - 1];
      Robot *r2 = comp->robots[comp->robots_count - 2];
      comp->robots_count -= 2;
      comp->robots_in_fight += 2;
      pthread_mutex_unlock(&comp->array);
 
      FightArgs *fightArgs = malloc(sizeof(FightArgs));
      fightArgs->robot1 = r1;
      fightArgs->robot2 = r2;
      fightArgs->comp = comp;

      pthread_t fight;
      pthread_create(&fight, NULL, Fight, fightArgs);
     }
   }
  pthread_mutex_unlock(&comp->wait_competition);
  return NULL;
}

void CompetitionStart(Competition* comp) {
  pthread_t management_thread;
  pthread_create(&management_thread, NULL, Management, comp);
}

const Robot* CompetitionStop(Competition* comp) {
  pthread_mutex_lock(&comp->lock);
  comp->competition_stop = true;
  pthread_mutex_lock(&comp->array);
  // SIGNAL when competition is finished
  if (COMPETITION_FINISHED(comp)) {
    pthread_cond_signal(&comp->cond_wait_robot);
  }
  pthread_mutex_unlock(&comp->array);
  pthread_mutex_unlock(&comp->lock);
  pthread_mutex_lock(&comp->wait_competition);

  return comp->robots[0];
}

bool CompetitionAddParticipant(Competition* comp, const Robot* robot) {
  pthread_mutex_lock(&comp->lock);
  if (comp->competition_stop) {
    pthread_mutex_unlock(&comp->lock);
    return false;
  }
  
  pthread_mutex_unlock(&comp->lock);
  pthread_mutex_lock(&comp->array);
  comp->robots[comp->robots_count] = robot;
  comp->robots_count += 1;
  if (comp->robots_count == 2) {
    pthread_cond_signal(&comp->cond_wait_robot);
  }
  pthread_mutex_unlock(&comp->array);

  return true;
}

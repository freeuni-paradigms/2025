#include "competition.h"

#include <stdlib.h>

#include "robot.h"

#define COMPETITION_FINISHED(comp) (comp->all_participants == 1 && comp->stop)

void CompetitionInit(Competition* comp) {
  comp->stop = false;
  comp->length = 0;
  comp->all_participants = 0;
  pthread_mutex_init(&comp->stop_lock, NULL);
  pthread_mutex_init(&comp->m, NULL);
  pthread_mutex_lock(&comp->m);
  pthread_mutex_init(&comp->modify_array, NULL);
  pthread_mutex_init(&comp->mutex_all_participant, NULL);
  pthread_cond_init(&comp->cond_wait_robot, NULL);
}

typedef struct RobotFight {
  Robot *r1;
  Robot *r2;
  Competition *comp;
} RobotFight;

void *Fight(void *data) {
  RobotFight *robotFight = (RobotFight *) data;
  Competition *comp = robotFight->comp;

  Robot *winner = robotFight->r2;
  if (RobotFightWith(robotFight->r1, robotFight->r2)) {
    winner = robotFight->r1;
  }
  
  pthread_mutex_lock(&comp->mutex_all_participant);
  comp->all_participants -= 1;
  pthread_mutex_unlock(&comp->mutex_all_participant);

  pthread_mutex_lock(&comp->modify_array);
  comp->robots[comp->length] = winner;
  comp->length += 1;
  if (comp->length == 2 || COMPETITION_FINISHED(comp)) {
    pthread_cond_signal(&comp->cond_wait_robot);
  }
  pthread_mutex_unlock(&comp->modify_array);

  free(robotFight);
}

void *CompetitionManager(void *data) {
  Competition *comp = (Competition *) data;

  while (1) {
    pthread_mutex_lock(&comp->stop_lock);
    pthread_mutex_lock(&comp->mutex_all_participant);
    if (COMPETITION_FINISHED(comp)) {
      pthread_mutex_unlock(&comp->m);
      pthread_mutex_unlock(&comp->mutex_all_participant);
      pthread_mutex_unlock(&comp->stop_lock);
      break;
    }
    pthread_mutex_unlock(&comp->mutex_all_participant);
    pthread_mutex_unlock(&comp->stop_lock);

    pthread_mutex_lock(&comp->modify_array);
    if (comp->length < 2) {
      pthread_cond_wait(&comp->cond_wait_robot, &comp->modify_array);
      pthread_mutex_unlock(&comp->modify_array);
    }
    if (comp->length < 2) {
      continue;
    }
    RobotFight *robotFight = malloc(sizeof(RobotFight));
    robotFight->r1 = comp->robots[comp->length - 1];
    robotFight->r2 = comp->robots[comp->length - 2];
    robotFight->comp = comp;
    comp->length -= 2;
    pthread_mutex_unlock(&comp->modify_array);

    pthread_t new_fight;
    pthread_create(&new_fight, NULL, Fight, robotFight);
  }
}

void CompetitionStart(Competition* comp) {
  // IMPLEMENT
  pthread_t competition;
  pthread_create(&competition, NULL, CompetitionManager, comp);  
}

const Robot* CompetitionStop(Competition* comp) {
  pthread_mutex_lock(&comp->stop_lock);
  comp->stop = true;
  pthread_mutex_unlock(&comp->stop_lock);

  pthread_mutex_lock(&comp->modify_array);
  if (COMPETITION_FINISHED(comp)) {
    pthread_cond_signal(&comp->cond_wait_robot);
  }
  pthread_mutex_unlock(&comp->modify_array);

  pthread_mutex_lock(&comp->m);

  Robot *winner = comp->robots[0];
  return winner;
}

bool CompetitionAddParticipant(Competition* comp, const Robot* robot) {

  pthread_mutex_lock(&comp->stop_lock);
  if (comp->stop) {
    pthread_mutex_unlock(&comp->stop_lock);
    return false;
  }
  pthread_mutex_unlock(&comp->stop_lock);


  pthread_mutex_lock(&comp->modify_array);
  comp->robots[comp->length] = robot;
  comp->length += 1;

  if (comp->length == 2) {
    pthread_cond_signal(&comp->cond_wait_robot);
  }

  pthread_mutex_unlock(&comp->modify_array);

  pthread_mutex_lock(&comp->mutex_all_participant);
  comp->all_participants += 1;
  pthread_mutex_unlock(&comp->mutex_all_participant);

  return true;
}

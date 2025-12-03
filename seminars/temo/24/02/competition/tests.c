#include "robot.h"
#include "competition.h"

#include <stdio.h>
#include <unistd.h>

#define ASSERT(expr) {							\
    if (!(expr)) {							\
    printf("%s:%d: Assertion failed: %s\n", __FILE__, __LINE__, #expr);	\
    return false;							\
  }									\
}

bool FightRobots(const Robot* x, const Robot* y) {
  printf("New fight: %d %d\n", x->id, y->id);
  sleep((x->id + y->id) / 5.0);
  if (x->id > y->id) {
    printf("Fight %d %d: winner is %d\n", x->id, y->id, x->id);
  } else {
    printf("Fight %d %d: winner is %d\n", x->id, y->id, y->id);
  }
  return x->id > y->id;
}

int main(int argc, char** argv) {
  Competition comp;
  printf("Initializing competition ..\n");
  CompetitionInit(&comp);
  printf("Initialization finished\n");
  printf("Starting competition ..\n");
  CompetitionStart(&comp);
  printf("Competition started\n");
  Robot robots[100];
  for (int i = 0; i < 10; ++i) {
    robots[i].id = i;
    robots[i].fight_fn = FightRobots;
    printf("Adding participant %d ..\n", i);
    if (CompetitionAddParticipant(&comp, &robots[i])) {
      printf("Participant %d entered competition\n", i);
    } else {
      printf("Participant %d was rejected\n", i);
    }
  }
  ASSERT(&robots[9] == CompetitionStop(&comp));
  return 0;
}

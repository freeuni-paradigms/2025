#include "maintenance.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(0));
  int num_tables = 4;
  int soft_size = 3;
  int hard_size = 2;
  printf("Setting up server room for %d tables, hardware team size: %d, software team size: %d\n",
	 num_tables, hard_size, soft_size);
  SetUpServerRoom(num_tables, hard_size, soft_size);
  return 0;
}

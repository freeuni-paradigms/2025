#include "maintenance.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test(int num_tables, int soft_size, int hard_size) {
  printf("Setting up server room for %d tables, hardware team size: %d, software team size: %d\n",
	 num_tables, hard_size, soft_size);
  SetUpServerRoom(num_tables, hard_size, soft_size);
}

int main() {
  srand(time(0));
  test(1, 1, 1);
  test(4, 3, 2);
  return 0;
}

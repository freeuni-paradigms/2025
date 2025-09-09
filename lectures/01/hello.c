#include <stdio.h>

int main(int argc, char** argv) {
  printf("NUM ARGS: %d\n", argc);
  for (int i = 0; i < argc; ++i) {
	printf("%d-th ARG: %s\n", i, argv[i]);
  }
  printf("hello freeuni!\n");
  return 0;
}

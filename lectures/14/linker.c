// #include <stdio.h> printf
#include <stdlib.h> malloc/free
#include <assert.h> assert
#include <stddef.h> NULL

// DECLARATION
// DEFINITION

int main(int argc, char** argv) {
  void* memory = malloc(40);
  assert(memory != NULL);
  printf("SUCCESS\n");
  free(memory);
  return 0;
}

  asdasd
  ..

  ...

  ...


  ..
  ..
  JUMP +400
  ..
  ..
  PC = PC - 100
  JUMP
  ..
  ..
  CALL printf
  ..
  CALL free
  ..
  RET

// PREPROCESSOR
//   C (c + macro) -> C #define #include #ifdef ....
//   gcc -E
// TRANSLATOR
//   C (c) -> object file -s S
//   label -> instruction
//   CALL
// LINKER
//  o1 o2 ... oN -> executable
//  main -> CALL main
//  CALL -> JUMP offset + remove label

/* A -> X */
/* B -> X */
/* C -> A .. B */



// #include <stdio.h> // printf
#include <stdlib.h> // malloc/free
#include <assert.h> // assert
#include <stddef.h> // NULL

// static
// dynamic

// int malloc(int)
//   void*
// int free(void*)
//   void
// int assert(bool)

// no-op (void)0
/* #ifndef NDEBUG */
/* #define assert(cond)							\ */
/*   ((cond) ? (void)0 : exit(1)) */
/* #else */
/* #define assert(cond) (void)0 */
/* #endif */

// int printf(char*, int, int, float)
// int printf(char*, int)


int main(int argc, char** argv) {
  void* memory = malloc(40);
  assert(memory != NULL);
  int k = printf("%d SUCCESS %d %f\n", 1, 2, 3.7);
  printf("%d\n", k);
  free(memory);
  return 0;
}



1 SUCCESS 2 3.700000\n

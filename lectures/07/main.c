#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StrFree(void* addr) {
  free(*(char**)addr);
}

void NoOpFree(void* addr) {
  // empty
}

int main() {
  Stack s;
  StackInit(&s, sizeof(char*), NULL);
  char* a = strdup("freeuni");
  char* b = strdup("agruni");
  char* c = strdup("abcd");
  StackPush(&s, &a);
  StackPush(&s, &b);
  StackPush(&s, &c);
  char* x;
  StackPop(&s, &x);
  printf("%s\n", x);
  free(x);
  /* StackPop(&s, &x); */
  /* printf("%s\n", x); */
  /* for (int i = 0; i < 10; i++) { */
  /* 	StackPush(&s, &i); */
  /* } */
  /* while (StackSize(&s) > 0) { */
  /* 	int elem; */
  /* 	StackPop(&s, &elem); */
  /* 	printf("%d\n", elem); */
  /* } */
  StackDestroy(&s);
  return 0;
}

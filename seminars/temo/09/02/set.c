#include <stdio.h>
#include "sorted_set.h"
#include <string.h>

int compareStr(const void *a, const void *b) {
  return strcmp(a, b);
}

int main() {
  sortedset s;

  SetNew(&s, sizeof(char *), compareStr);
  
  int x = SetAdd(&s, strdup("str"));
  printf("%d\n", x);

  printf("%p\n%s\n", SetSearch(&s, strdup("n")), (char *)SetSearch(&s, strdup("str")));

  return 0;
}

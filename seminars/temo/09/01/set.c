#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "sorted_set.h"

//typedef struct { 
//  void *base;
//  int elemSize;
//  int logLen;
//  int allocLen;
//  int (*cmpfn)(const void *, const void *);
//} sortedset; 
//
//void SetNew(sortedset *set, int elemSize,  
//            int (*cmpfn)(const void *, const void *));
//bool SetAdd(sortedset *set, const void *elemPtr); 
//void *SetSearch(sortedset *set, const void *elemPtr); 

int compareStrings(const void *a, const void *b) {
  return strcmp(a, b);
}

int main() {
  sortedset s;
  SetNew(&s, sizeof(char *), compareStrings);
  SetAdd(&s, strdup("s"));
  char *result = (char *)SetSearch(&s, strdup("s"));
  printf("%s\n", result);
  return 0;
}


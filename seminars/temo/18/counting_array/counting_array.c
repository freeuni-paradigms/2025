#include "counting_array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void CountingArrayInit(CountingArray* a, int elem_size, CmpFn cmp_fn, FreeFn free_fn) {
  // IMPLEMENT
}

void CountingArrayDestroy(CountingArray* a) {
  // IMPLEMENT
}

int CountingArraySize(CountingArray* a) {
  // IMPLEMENT
  return 0;
}

void* CountingArrayGet(CountingArray* a, int index) {
  // IMPLEMENT
  return NULL;
}

bool CountingArrayInsert(CountingArray* a, void* elem) {
  // IMPLEMENT
}

void CountingArrayRemove(CountingArray* a, void* elem) {
  // IMPLEMENT
}

void CountingArrayMerge(CountingArray* a, CountingArray* o) {
  // IMPLEMENT
}

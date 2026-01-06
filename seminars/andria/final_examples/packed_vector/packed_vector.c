#include "packed_vector.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void VectorInit(Vector* v, int n) {
  // IMPLEMENT
}

void VectorDestroy(Vector* v) {
  // IMPLEMENT
}

void VectorSet(Vector* v, int index, int elem_size, void* elem) {
  // IMPLEMENT
}

void* VectorGet(Vector* v, int index, int* elem_size) {
  // IMPLEMENT
  return NULL;
}

void VectorSwap(Vector* v, int i, int j) {
  // IMPLEMENT
}

void VectorMap(Vector* v, MapFn map_fn, void* aux) {
  // IMPLEMENT
}

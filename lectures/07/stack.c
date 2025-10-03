#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define INIT_ALLOC_LEN 4
#define ELEM_ADDR(s, i) (char*)s->base + i * s->elem_size

// magic number
void StackInit(Stack* s, int elem_size, FreeFn free_fn) {
  s->elem_size = elem_size;
  s->base = malloc(INIT_ALLOC_LEN * s->elem_size);
  assert(s->base != NULL);
  s->log_len = 0;
  s->alloc_len = INIT_ALLOC_LEN;
  s->free_fn = free_fn;
}

void StackDestroy(Stack* s) {
  if (s->free_fn != NULL) {
	for (int i = 0; i < s->log_len; i++) {
	  s->free_fn(ELEM_ADDR(s, i));
	}
  }
  free(s->base);
}

void StackPush(Stack* s, void* v) {
  if (s->log_len == s->alloc_len) {
	s->alloc_len *= 2;
	s->base = realloc(s->base, s->alloc_len * s->elem_size);
	// assert(bool) -> false crash
	// precondition check
	assert(s->base != NULL);
  }
  void* elem_addr = ELEM_ADDR(s, s->log_len);
  memcpy(elem_addr, v, s->elem_size);
  // s->base[s->log_len] = v;
  s->log_len++;
}

// memory ownership
void StackPop(Stack* s, void* addr) {
  assert(s->log_len > 0);
  s->log_len--;
  void* elem_addr = ELEM_ADDR(s, s->log_len);
  memcpy(addr, elem_addr, s->elem_size);
}

int StackSize(Stack* s) {
  return s->log_len;
}

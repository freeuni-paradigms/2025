#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* int lsearch(int* a, int num_elems, int v) { */
/*   for (int i = 0; i < num_elems; ++i) { */
/* 	// if (*(a + i) == v) { */
/* 	if (a[i] == v) { */
/* 	  return i; */
/* 	} */
/*   } */
/*   return -1; */
/* } */

typedef int(*CmpFn)(void*, void*);

// <0 -- a < b
// >0 -- a > b
// =0 -- a == b
int IntCmp(void* a, void* b) {
  return (*(int*)a) - (*(int*)b);
}

int StrCmp(void* a, void* b) {
  char* s = *(char**)a;
  char* t = *(char**)b;
  return strcmp(s, t);
}

// memcmp - memory compare - addr1 - addr2 - number of bytes
int lsearch(
			void* a,
			int num_elems,
			void* v,
			int elem_size,
			CmpFn cmp) {
			// int(*cmp)(void*, void*)) {
  for (int i = 0; i < num_elems; ++i) {
	void* elem_addr = (char*)a + i * elem_size; // char* + k -- void* + k
	// if (*(a + i) == v) {
	if (cmp(elem_addr, v) == 0) {
	  return i;
	}
  }
  return -1;
}

typedef struct {
  int num;
  int denum;
}  Fraction;

// literal
// string literal
// int literal

int main() {
  int a[5] = {1, 3, 2, 10, -5};
  int k = 10;
  printf("%d\n", lsearch(a, 5, &k, sizeof(int), IntCmp));
  /* double d[3] = {1.2, 2.3, 3.4}; */
  /* double q = 2.3; */
  /* printf("%d\n", lsearch(d, 3, &q, sizeof(double))); */
  /* Fraction f[2]; */
  /* f[0].num = 1; */
  /* f[0].denum = 2; */
  /* f[1].num = 3; */
  /* f[1].denum = 4; */
  /* Fraction t; */
  /* t.num = 1; */
  /* t.denum = 3; */
  /* printf("%d\n", lsearch(f, 2, &t, sizeof(Fraction))); */
  char* s[3] = {
	strdup("freeuni"),
	strdup("agruni"),
	strdup("abcd"),
  };
  char* r = "freeuni";
  printf("%d\n", lsearch(s, 3, &r, sizeof(char*), StrCmp));
  return 0;
}

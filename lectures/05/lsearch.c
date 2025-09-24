#include <stdio.h>

int lsearch(int* a, int num_elems, int v) {
  for (int i = 0; i < num_elems; ++i) {
	// if (*(a + i) == v) {
	if (a[i] == v) {
	  return i;
	}
  }
  return -1;
}

// memcmp - memory compare - addr1 - addr2 - number of bytes
int lsearch(void* a, int num_elems, void* v, int elem_size) {
  for (int i = 0; i < num_elems; ++i) {
	void* elem_addr = (char*)a + i * elem_size; // char* + k -- void* + k
	// if (*(a + i) == v) {
	if (memcmp(v, elem_addr, elem_size) == 0) {
	  return i;
	}
  }
  return -1;
}

int main() {
  int a[5] = {1, 3, 2, 10, -5};
  int k = 10;
  int pos = lsearch(a, 5, &k, sizeof(int));
  printf("%d\n", pos);
  printf("%d\n", lsearch(a, 5, -10));
  char* s[3] = {
	strdup("freeuni"),
	strdup("agruni"),
	strdup("abcd"),
  };
  printf("%d\n", lsearch(s, 3, "agruni"));
  return 0;
}

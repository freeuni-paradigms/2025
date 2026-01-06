#include "packed_vector.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_TRUE(a) {						\
    bool actual = (a);							\
    if (!actual) {							\
      printf("%s:%d Assertion failed: expected true got false\n", __FILE__, __LINE__); \
      return false;							\
    }									\
  }

#define ASSERT_FALSE(a) {						\
    bool actual = (a);							\
    if (actual) {							\
      printf("%s:%d Assertion failed: expected false got true\n", __FILE__, __LINE__); \
      return false;							\
    }									\
  }

#define ASSERT_DOUBLE_EQ(a, b) {						\
    double expected = (a);							\
    double actual = (b);							\
    if (abs(expected - actual) > 0.000001) {										\
      printf("%s:%d Assertion failed: expected %f got %f\n", __FILE__, __LINE__, expected, actual); \
      return false;							\
    }									\
  }

#define ASSERT_INT_EQ(a, b) {						\
    int expected = (a);							\
    int actual = (b);							\
    if (expected != actual) {						\
      printf("%s:%d Assertion failed: expected %d got %d\n", __FILE__, __LINE__, expected, actual); \
      return false;							\
    }									\
  }

#define ASSERT_STR_EQ(a, b) {						\
    char* expected = (a);						\
    char* actual = (b);							\
    if (strcmp(expected, actual) != 0) {				\
      printf("%s:%d Assertion failed: expected \"%s\" got \"%s\"\n", __FILE__, __LINE__, expected, actual); \
      return false;							\
    }									\
  }

#define ASSERT_MEM_EQ(a, b, size) {					\
    void* expected = (a);						\
    void* actual = (b);							\
    if (memcmp(expected, actual, size) != 0) {								\
      printf("%s:%d Assertion failed: memory does not match\n", __FILE__, __LINE__); \
      return false;							\
    }									\
  }

#define TEST(t) {				\
    printf("-- TESTING: %s\n", #t);		\
    if (t()) {					\
      printf("TEST %s: SUCCEEDED\n", #t);	\
    }						\
    else {					\
      printf("TEST %s: FAILED\n", #t);		\
    }						\
    printf("####\n\n");				\
  }

int IntCmp(void* a, void* b) {
  return *(int*)a - *(int*)b;
}

int StrCmp(void* a, void* b) {
  return strcmp(*(char**)a, *(char**)b);
}

void StrFree(void* a) {
  free(*(char**)a);
}

// Integers

bool Empty() {
  Vector v;
  VectorInit(&v, 5);
  VectorDestroy(&v);
  return true;
}

bool Ints() {
  Vector v;
  VectorInit(&v, 3);
  int x = 1;
  VectorSet(&v, 0, sizeof(int), &x);
  x = 2;
  VectorSet(&v, 1, sizeof(int), &x);
  x = 3;
  VectorSet(&v, 2, sizeof(int), &x);
  int size;
  int* y;
  y = VectorGet(&v, 0, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(1, *y);
  y = VectorGet(&v, 1, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(2, *y);
  y = VectorGet(&v, 2, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(3, *y);
  VectorDestroy(&v);
  return true;
}

bool Ints_Overwrite() {
  Vector v;
  VectorInit(&v, 3);
  int x = 1;
  VectorSet(&v, 0, sizeof(int), &x);
  x = 2;
  VectorSet(&v, 1, sizeof(int), &x);
  x = 3;
  VectorSet(&v, 2, sizeof(int), &x);
  int size;
  int* y;
  y = VectorGet(&v, 0, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(1, *y);
  y = VectorGet(&v, 1, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(2, *y);
  y = VectorGet(&v, 2, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(3, *y);
  // Overwrite
  x = 4;
  VectorSet(&v, 0, sizeof(int), &x);
  x = 5;
  VectorSet(&v, 1, sizeof(int), &x);
  x = 6;
  VectorSet(&v, 2, sizeof(int), &x);
  // Checks
  y = VectorGet(&v, 0, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(4, *y);
  y = VectorGet(&v, 1, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(5, *y);
  y = VectorGet(&v, 2, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(6, *y);
  VectorDestroy(&v);
  return true;
}

bool Ints_Swap() {
  Vector v;
  VectorInit(&v, 50);
  for (int i = 0; i < 50; ++i) {
	VectorSet(&v, i, sizeof(int), &i);
  }
  for (int i = 0; i < 50; ++i) {
	int size;
	int* k = VectorGet(&v, i, &size);
	ASSERT_INT_EQ(sizeof(int), size);
	ASSERT_INT_EQ(i, *k);
  }
  for (int i = 0; i < 25; ++i) {
	VectorSwap(&v, i, 49 - i);
  }
  for (int i = 0; i < 50; ++i) {
	int size;
	int* k = VectorGet(&v, i, &size);
	ASSERT_INT_EQ(sizeof(int), size);
	ASSERT_INT_EQ(49 - i, *k);
  }
  VectorDestroy(&v);
  return true;
}

typedef struct {
  int count;
  int sum;
} SumData;

void IntSum(int index, int size, void* elem, void* aux) {
  SumData* d = aux;
  d->count++;
  d->sum += *(int*)elem;
}

bool Ints_Sum_With_Map() {
  Vector v;
  VectorInit(&v, 100);
  for (int i = 0; i < 100; ++i) {
	int k = 10 * i;
	VectorSet(&v, i, sizeof(int), &k);
  }
  SumData d;
  d.count = 0;
  d.sum = 0;
  VectorMap(&v, IntSum, &d);
  ASSERT_INT_EQ(100, d.count);
  ASSERT_INT_EQ(10 * 99 * 100 / 2, d.sum);
  VectorDestroy(&v);
  return true;
}

bool Ints_InsertGet() {
  Vector v;
  VectorInit(&v, 100);
  for (int i = 100; i > 0; --i) {
	int k = 20 * i;
	VectorSet(&v, 100 - i, sizeof(int), &k);
  }
  for (int i = 0; i < 100; ++i) {
	int size;
	int* k = VectorGet(&v, i, &size);
	ASSERT_INT_EQ(sizeof(int), size);
	ASSERT_INT_EQ(20 * (100 - i), *k);
  }
  VectorDestroy(&v);
  return true;
}

bool Mixed() {
  Vector v;
  VectorInit(&v, 3);
  int x = 5;
  char* y = "freeuni";
  double z = 3.4;
  VectorSet(&v, 0, sizeof(int), &x);
  VectorSet(&v, 1, strlen(y), y);
  VectorSet(&v, 2, sizeof(double), &z);
  int size;
  int* a = VectorGet(&v, 0, &size);
  ASSERT_INT_EQ(sizeof(int), size);
  ASSERT_INT_EQ(5, *a);
  char* b = VectorGet(&v, 1, &size);
  ASSERT_INT_EQ(strlen(y), size);
  ASSERT_TRUE(0 == strncmp(y, b, strlen(y)));
  double* c = VectorGet(&v, 2, &size);
  ASSERT_DOUBLE_EQ(3.4, *c);
  ASSERT_MEM_EQ(&z, c, sizeof(double));
  VectorDestroy(&v);
  return true;
}

void MixedSum(int index, int size, void* elem, void* aux) {
  SumData* d = aux;
  d->count++;
  if (size == 4) {
	d->sum += *(int*)elem;
  } else {
	d->sum += size;
  }
}

bool Mixed_Map() {
  Vector v;
  VectorInit(&v, 4);
  int x = 5;
  char* y = "hi";
  int z = 10;
  char* w = "uni";
  VectorSet(&v, 0, sizeof(int), &x);
  VectorSet(&v, 1, strlen(y), y);
  VectorSet(&v, 2, sizeof(int), &z);
  VectorSet(&v, 3, strlen(w), w);
  SumData d;
  d.count = 0;
  d.sum = 0;
  VectorMap(&v, MixedSum, &d);
  ASSERT_INT_EQ(4, d.count);
  ASSERT_INT_EQ(5 + 2 + 10 + 3, d.sum);
  VectorDestroy(&v);
  return true;
}

bool Mixed_Swap() {
  Vector v;
  VectorInit(&v, 4);
  int x = 5;
  char* y = "a";
  int z = 10;
  char* w = "bcdefg";
  VectorSet(&v, 0, sizeof(int), &x);
  VectorSet(&v, 1, strlen(y), y);
  VectorSet(&v, 2, sizeof(int), &z);
  VectorSet(&v, 3, strlen(w), w);
  VectorSwap(&v, 0, 1);
  VectorSwap(&v, 2, 3);
  int size;
  char* a = VectorGet(&v, 0, &size);
  ASSERT_INT_EQ(1, size);
  ASSERT_MEM_EQ("a", a, 1);
  int* b = VectorGet(&v, 1, &size);
  ASSERT_INT_EQ(4, size);
  ASSERT_INT_EQ(5, *b);
  char* c = VectorGet(&v, 2, &size);
  ASSERT_INT_EQ(6, size);
  ASSERT_MEM_EQ("bcdefg", c, 6);
  int* d = VectorGet(&v, 3, &size);
  ASSERT_INT_EQ(4, size);
  ASSERT_INT_EQ(10, *d);
  VectorDestroy(&v);
  return true;
}

int main(int argc, char** argv) {
  TEST(Empty);
  TEST(Ints);
  TEST(Ints_Overwrite);
  TEST(Ints_Swap);
  TEST(Ints_Sum_With_Map);
  TEST(Ints_InsertGet);
  TEST(Mixed);
  TEST(Mixed_Map);
  TEST(Mixed_Swap);
  return 0;
}

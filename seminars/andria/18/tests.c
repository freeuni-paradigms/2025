#include "counting_array.h"

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
  CountingArray a;
  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);
  ASSERT_INT_EQ(0, CountingArraySize(&a));
  CountingArrayDestroy(&a);
  return true;
}

bool InsertGet() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  for (int i = 0; i < 3; ++i) {
    CountingArrayInsert(&a, &i);
  }
  ASSERT_INT_EQ(3, CountingArraySize(&a));

  for (int i = 0; i < 3; ++i) {
    ASSERT_INT_EQ(i, *(int*)CountingArrayGet(&a, i));
  }
  CountingArrayDestroy(&a);
}

bool InsertMany() {
  CountingArray a;
  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);

  for (int i = 0; i < 10000; ++i) {
    CountingArrayInsert(&a, &i);
  }

  for (int i = 0; i < 10000; ++i) {
    CountingArrayRemove(&a, &i);
  }

  CountingArrayDestroy(&a);
  return true;
}

bool RemoveNonExistent() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  for (int i = 0; i < 3; ++i) {
    CountingArrayInsert(&a, &i);
  }

  int x = 3;
  CountingArrayRemove(&a, &x);
  ASSERT_INT_EQ(3, CountingArraySize(&a));

  CountingArrayDestroy(&a);
  return true;
}

bool InsertRemove() {
  CountingArray a;
  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);

  ASSERT_INT_EQ(0, CountingArraySize(&a));

  for (int i = 0; i < 3; ++i) {
    CountingArrayInsert(&a, &i);
    ASSERT_INT_EQ(i + 1, CountingArraySize(&a));
  }

  ASSERT_INT_EQ(3, CountingArraySize(&a));

  for (int i = 0; i < 3; ++i) {
    CountingArrayRemove(&a, &i);
    ASSERT_INT_EQ(2 - i, CountingArraySize(&a));
  }

  CountingArrayDestroy(&a);
  return true;
}

bool InsertRemoveMany() {
  CountingArray a;
  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);

  for (int i = 0; i < 10000; ++i) {
    CountingArrayInsert(&a, &i);
  }

  ASSERT_INT_EQ(10000, CountingArraySize(&a));

  for (int i = 0; i < 10000; ++i) {
    CountingArrayRemove(&a, &i);
    ASSERT_INT_EQ(9999 - i, CountingArraySize(&a));
  }

  CountingArrayDestroy(&a);
  return true;
}

bool InsertGetDuplicate() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  int x = 1;
  CountingArrayInsert(&a, &x);
  CountingArrayInsert(&a, &x);
  CountingArrayInsert(&a, &x);

  ASSERT_INT_EQ(1, CountingArraySize(&a));
  ASSERT_INT_EQ(1, *(int*)CountingArrayGet(&a, 0));

  CountingArrayDestroy(&a);
  return true;
}

bool InsertRemoveDuplicate() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  int x = 1;
  CountingArrayInsert(&a, &x);
  ASSERT_INT_EQ(1, CountingArraySize(&a));

  CountingArrayInsert(&a, &x);
  ASSERT_INT_EQ(1, CountingArraySize(&a));
  ASSERT_INT_EQ(1, *(int*)CountingArrayGet(&a, 0));

  CountingArrayRemove(&a, &x);
  ASSERT_INT_EQ(1, CountingArraySize(&a));
  ASSERT_INT_EQ(1, *(int*)CountingArrayGet(&a, 0));

  CountingArrayRemove(&a, &x);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  CountingArrayDestroy(&a);
  return true;
}

bool StringsInsertGet() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(char*), StrCmp, StrFree);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  char* x = strdup("free");
  CountingArrayInsert(&a, &x);

  char* y = strdup("uni");
  CountingArrayInsert(&a, &y);

  char* z = strdup("hello world!");
  CountingArrayInsert(&a, &z);

  // Lexographic Order: "free", "hello world!", "uni"

  ASSERT_INT_EQ(3, CountingArraySize(&a));
  ASSERT_STR_EQ("free", *(char**)CountingArrayGet(&a, 0));
  ASSERT_STR_EQ("uni", *(char**)CountingArrayGet(&a, 2));
  ASSERT_STR_EQ("hello world!", *(char**)CountingArrayGet(&a, 1));

  CountingArrayDestroy(&a);
  return true;
}

bool StringsInsertGetMany() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(char*), StrCmp, StrFree);

  for (int i = 0; i < 1000; ++i) {
    char* x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);
    CountingArrayInsert(&a, &x);
  }

  ASSERT_INT_EQ(10000, CountingArraySize(&a));

  for (int i = 0; i < 1000; ++i) {
    char* x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);
    CountingArrayRemove(&a, &x);
    ASSERT_INT_EQ(9999 - i, CountingArraySize(&a));
  }

  CountingArrayDestroy(&a);
  return true;
}

bool StringsInsertRemove() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(char*), StrCmp, StrFree);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  char* x = strdup("free");
  CountingArrayInsert(&a, &x);

  char* y = strdup("uni");
  CountingArrayInsert(&a, &y);

  char* z = strdup("hello world!");
  CountingArrayInsert(&a, &z);

  ASSERT_INT_EQ(3, CountingArraySize(&a));

  CountingArrayRemove(&a, &x);
  ASSERT_INT_EQ(2, CountingArraySize(&a));

  CountingArrayRemove(&a, &y);
  ASSERT_INT_EQ(1, CountingArraySize(&a));

  CountingArrayRemove(&a, &z);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  CountingArrayDestroy(&a);

  return true;
}

bool StringsInsertGetDuplicate() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(char*), StrCmp, StrFree);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  char* x = strdup("free");
  CountingArrayInsert(&a, &x);

  x = strdup("free");
  CountingArrayInsert(&a, &x);

  x = strdup("free");
  CountingArrayInsert(&a, &x);

  ASSERT_INT_EQ(1, CountingArraySize(&a));
  ASSERT_STR_EQ("free", *(char**)CountingArrayGet(&a, 0));
  CountingArrayDestroy(&a);
  return true;
}

bool StringsInsertRemoveDuplicate() {
  CountingArray a;

  CountingArrayInit(&a, sizeof(char*), StrCmp, StrFree);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  char* x = strdup("free");
  CountingArrayInsert(&a, &x);
  ASSERT_INT_EQ(1, CountingArraySize(&a));

  x = strdup("free");
  CountingArrayInsert(&a, &x);
  ASSERT_INT_EQ(1, CountingArraySize(&a));
  ASSERT_STR_EQ("free", *(char**)CountingArrayGet(&a, 0));

  x = "free";
  CountingArrayRemove(&a, &x);
  ASSERT_INT_EQ(1, CountingArraySize(&a));
  ASSERT_STR_EQ("free", *(char**)CountingArrayGet(&a, 0));

  CountingArrayRemove(&a, &x);
  ASSERT_INT_EQ(0, CountingArraySize(&a));

  CountingArrayDestroy(&a);
  return true;
}

bool Merge() {
  CountingArray a;
  CountingArray b;

  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);
  CountingArrayInit(&b, sizeof(int), IntCmp, /*free_fn=*/NULL);

  for (int i = 0; i < 500; ++i) {
    CountingArrayInsert(&a, &i);
  }

  for (int i = 500; i < 1000; ++i) {
    CountingArrayInsert(&b, &i);
  }

  ASSERT_INT_EQ(500, CountingArraySize(&a));
  ASSERT_INT_EQ(500, CountingArraySize(&b));

  CountingArrayMerge(&a, &b);
  ASSERT_INT_EQ(1000, CountingArraySize(&a));

  for (int i = 0; i < 1000; ++i) {
    ASSERT_INT_EQ(i, *(int *)CountingArrayGet(&a, i));
  }
  CountingArrayDestroy(&a);
  return true;
}

bool MergeOverlap() {
  CountingArray a;
  CountingArrayInit(&a, sizeof(int), IntCmp, /*free_fn=*/NULL);
  CountingArray b;
  CountingArrayInit(&b, sizeof(int), IntCmp, /*free_fn=*/NULL);

  for (int i = 0; i < 500; ++i) {
    CountingArrayInsert(&a, &i);
  }

  for (int i = 400; i < 1000; ++i) {
    CountingArrayInsert(&b, &i);
  }

  ASSERT_INT_EQ(500, CountingArraySize(&a));
  ASSERT_INT_EQ(600, CountingArraySize(&b));

  CountingArrayMerge(&a, &b);
  ASSERT_INT_EQ(1000, CountingArraySize(&a));

  for (int i = 0; i < 1000; ++i) {
    ASSERT_INT_EQ(i, *(int *)CountingArrayGet(&a, i));
  }
  CountingArrayDestroy(&a);
  return true;
}

bool StringsMerge() {
  CountingArray a;
  CountingArray b;
  CountingArray combined; // manually merged

  CountingArrayInit(&a, sizeof(char*), StrCmp, StrFree);
  CountingArrayInit(&b, sizeof(char*), StrCmp, StrFree);
  CountingArrayInit(&combined, sizeof(char*), StrCmp, StrFree);

  for (int i = 0; i < 500; ++i) {
    char *x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&a, &x);
    x = strdup(x);
    CountingArrayInsert(&combined, &x);
  }

  for (int i = 500; i < 1000; ++i) {
    char *x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&b, &x);
    x = strdup(x);
    CountingArrayInsert(&combined, &x);
  }

  ASSERT_INT_EQ(500, CountingArraySize(&a));
  ASSERT_INT_EQ(500, CountingArraySize(&b));
  ASSERT_INT_EQ(1000, CountingArraySize(&combined));

  CountingArrayMerge(&a, &b);
  ASSERT_INT_EQ(1000, CountingArraySize(&a));

  for (int i = 0; i < 1000; ++i) {
    ASSERT_STR_EQ(*(char **)CountingArrayGet(&combined, i), *(char **)CountingArrayGet(&a, i));
  }

  CountingArrayDestroy(&a);
  CountingArrayDestroy(&combined);
  return true;
}

bool StringsMergeOverlap() {
  CountingArray a;
  CountingArray b;
  CountingArray combined; // manually merged

  CountingArrayInit(&a, sizeof(char*), StrCmp, StrFree);
  CountingArrayInit(&b, sizeof(char*), StrCmp, StrFree);
  CountingArrayInit(&combined, sizeof(char*), StrCmp, StrFree);

  for (int i = 0; i < 500; ++i) {
    char *x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&a, &x);

    x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&combined, &x);
  }

  for (int i = 400; i < 500; i++) {
    char *x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&b, &x);

    x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&combined, &x);
  }

  for (int i = 400; i < 1000; ++i) {
    char *x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&b, &x);

    x = malloc(32);
    assert(x != NULL);
    sprintf(x, "str-%d", i);

    CountingArrayInsert(&combined, &x);
  }

  ASSERT_INT_EQ(500, CountingArraySize(&a));
  ASSERT_INT_EQ(600, CountingArraySize(&b));
  ASSERT_INT_EQ(1000, CountingArraySize(&combined));

  CountingArrayMerge(&a, &b);
  ASSERT_INT_EQ(1000, CountingArraySize(&a));

  for (int i = 0; i < 1000; ++i) {
    ASSERT_STR_EQ(*(char **)CountingArrayGet(&combined, i), *(char **)CountingArrayGet(&a, i));
  }

  CountingArrayDestroy(&a);
  CountingArrayDestroy(&combined);
  return true;
}

int main(int argc, char** argv) {
  TEST(Empty);

  /* Integers */
  TEST(InsertGet);
  TEST(InsertMany);
  TEST(InsertRemove);
  TEST(RemoveNonExistent);
  TEST(InsertRemoveMany);

  /* Integers Duplicate */
  TEST(InsertGetDuplicate);
  TEST(InsertRemoveDuplicate);

  /* Strings */
  TEST(StringsInsertGet);
  TEST(StringsInsertRemove);

  /* Strings Duplicate */
  TEST(StringsInsertGetDuplicate);
  TEST(StringsInsertRemoveDuplicate);

  /* Merge */
  TEST(Merge);
  TEST(MergeOverlap);
  TEST(StringsMerge);
  TEST(StringsMergeOverlap);
  return 0;
}

#include "transform.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_INT_EQ(a, b) {						\
    int expected = (a);							\
    int actual = (b);							\
    if (expected != actual) {						\
      printf("%s:%d Assertion failed: expected %d got %d\n", __FILE__, __LINE__, expected, actual); \
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

bool AllEqual() {
  int heights[] = {2, 2, 2};
  ASSERT_INT_EQ(0, Transform(heights, 3));
  return true;
}

bool One() {
  int heights[] = {2, 1, 2};
  ASSERT_INT_EQ(1, Transform(heights, 3));
  return true;
}

bool Two() {
  int heights[] = {0, 1, 2};
  ASSERT_INT_EQ(2, Transform(heights, 3));
  return true;
}

bool Many() {
  int heights[] = {5, 3, 2, 5, 8, 10, 1};
  ASSERT_INT_EQ(5, Transform(heights, 7));
  return true;
}

int main(int argc, char** argv) {
  TEST(AllEqual);
  TEST(One);
  TEST(Two);
  TEST(Many);
  return 0;
}

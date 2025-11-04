#include "sum_3bit.h"

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

bool Empty() {
  char d[] = {0b00000000};
  ASSERT_INT_EQ(0, sum_3bit(d));
  return true;
}

bool OneByte() {
  char d[] = {0b01001100, 0b00000000};
  ASSERT_INT_EQ(5, sum_3bit(d));
  return true;
}

bool Example() {
  char d[] = {0b11001000, 0b01001110, 0b00000000};
  ASSERT_INT_EQ(14, sum_3bit(d));
  return true;
}

bool TEST_1() {
  char d[] = {5, 10, 11, 14, 50, 67, 91, 13, 0};
  ASSERT_INT_EQ(11, sum_3bit(d));
  return true;
}

bool TEST_2() {
  char d[] = {112, 231, 153, 230, 193, 151, 100, 200, 90, 0};
  ASSERT_INT_EQ(35, sum_3bit(d));
  return true;
}

int main(int argc, char** argv) {
  TEST(Empty);
  TEST(OneByte);
  TEST(Example);
  TEST(TEST_1);
  TEST(TEST_2);
  return 0;
}

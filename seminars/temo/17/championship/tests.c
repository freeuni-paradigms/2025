#include "championship.h"

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

bool OneByte() {
  char d[] = {0b01001100, 0b00000000};
  ASSERT_INT_EQ(1, FindWinner(d));
  return true;
}

bool ThreeTeams() {
  char d[] = {1, 67, 135, 159, 0};
  ASSERT_INT_EQ(7, FindWinner(d));
  return true;
}

bool TwoTeamsManyGames() {
  char d[] = {138, 10, 75, 147, 81, 0};
  ASSERT_INT_EQ(2, FindWinner(d));
  return true;
}

bool ManyGames() {
  char d[] = {136, 35, 89, 88, 143, 44, 17, 186, 142, 88, 120, 33, 12, 157, 75, 0};
  ASSERT_INT_EQ(3, FindWinner(d));
  return true;
}

int main(int argc, char** argv) {
  TEST(OneByte);
  TEST(ThreeTeams);
  TEST(TwoTeamsManyGames);
  TEST(ManyGames);
  return 0;
}

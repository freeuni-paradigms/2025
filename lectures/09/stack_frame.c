#include <stdio.h>

void A(int a, int b) {

  return;
}

void B() {
  int c;
  int d;
  printf("%d %d\n", c, d);
}

int main(int argc, char** argv) {
  // A(5, 7);
  B();
  return 0;
}

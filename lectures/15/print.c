#include <stdio.h>

void Init() {
  int i;
  int a[10];
  for (i = 0; i < 10; i++) {
	a[i] = i;
  }
}

void Print() {
  int a[10];
  int i;
  for (i = 0; i < 10; i++) {
	printf("%d\n", a[i]);
  }
}

int main(int argc, char** argv) {
  Init();
  Print();
  return 0;
}


Pipelining

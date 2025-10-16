int a[4];
int i;
for (i = 0; i < 4; i++) {
  a[i] = 0;
}
i--;

init
test
body
step


encoding/decoding
word - 4 byte - 32 bit
N instructions
2^K >= N
10 - 4

01 5
LI 01
ADD 011




PC - Program Counter



printf("%s asdasd %s asdfas %d asdfsdf %d", ., ., ., ..)

void qwe(int n, int* a) {
}


void foo(int bar, int* baz) {
  char c[4];
  short* s;
  ...
}

int main(int argc, char** argv) {
  int i = 4;
  foo(i, &i);
  return 0;
}



general activation record order / responsibility




int fact(int n) {
  if (n == 0) {
    return 1;
  }
  return n * fact(n - 1);
}

int main() {
  printf("%d\n", fact(3));
  return 0;
}











main:
LI x10 4
SW x10 0(sp)

ADDI sp sp -8
LW x10 8(sp)
SW x10 0(sp)	
ADDI x11 sp 8
SW x11 4(sp)
ADDI sp sp -4
SW ra 0(sp)
CALL foo // RA <- PC+4
LW ra 0(sp)
ADDI sp sp 12
RET






foo:
ADDI sp sp -8
lajhsdgljahsgd
ajshdgalsd
ADDI sp sp 8
RET // PC <- RA


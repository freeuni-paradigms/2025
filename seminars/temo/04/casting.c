#include <stdio.h>

int main() {

  // 00000101
  char c = 65;

  // 00000000 000000000 0000000 00000101
  int i = (int) c;

  printf("char c = %c \n int i = %d \n\n", c, i);


  //                  15    12            
  // 00000000 00000000 10010000 00010001
  int i1 = 17+ (1 << 15) + (1 << 12);

  // 10010000 00010001
  short s1 = (short) i1;
  unsigned short us1 = (unsigned short) i1;

  printf("int i1 = %d\nshorts1 = %d\nunsigned short us1 = %d\n\n", i1, s1, us1);

  // float - 000010000001000100
  // int   - 000000000000000010
  float f = 2.4;
  int fi = (int) f;
  printf("float f = %f\nint fi = %d\n\n", f, fi);
  
  float *f_pointer = &f;
  int fi_cast = *(int *)f_pointer;

  printf("int fi_cast = %d\n", fi_cast);

  return 0;
}

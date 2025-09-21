#include <stdio.h>

int main() {

  // 00000111
  char c = 7;
  // 00000000 00000111
  short s = (short) c;

  printf("char c ascii = %c\n", 65);
  printf("char c = %d\nshort s = %d\n\n", c, s);


  // 4 + 16
  // 0000000 00000000 10100000 00010100 
  int i1 = (1 << 15) + (1 << 13) + 20;

  // 10100000 00010100
  short s1 = (short) i1;
  unsigned int us1 = (unsigned short) i1;
  printf("int i1 = %d\nshort s1 = %d\nunsigned short us1 = %d\n\n", i1, s1, us1);

  // 0000000
  //                             -7 -8
  //          -1 -2 -3 ...         -23
  // SEEEEEEEEMMMMMMMMMMMMMMMMMMMMMM
  // (-1)^S * (1.M) * 2^(127-E)
  //
  // (-1)^0 * (1.25) * 2 ^ (127 - 127)
  //
  // S = 0    M = .25       E = 127
  //           -1 -2   
  //  0 01111111 01000000000000000000
  // ^
  float f = 1.25;
  int fi = (int) f;

  printf("int fi = %d\n", fi);

  // fi უნდა დავკასტოთ float-ზე თუ %f-ით გვინდა დავპრინტოთ
  // ამ შემთხვევაში როცა არ დავკასტეთ მაგალითად,
  // ორივე მნიშვნელობა f-ის გამოიტანა.
  // printf("float f = %f\nint fi = %f\n\n", f, fi); 
  printf("float f = %f\nint fi = %f\n\n", f, (float)fi); 

  float *f_address = &f;
  int fi_cast = *(int *)f_address; 

  printf("int fi_cast = %d\n\n", fi_cast);

  // 00000000 00000101
  short s2 = 5;
  // 01010100 01010101 00000000 00000101
  int i2 = *(int *)&s2;

  printf("s2 = %d\ni2 = %d\n", s2, i2);
  return 0;
}


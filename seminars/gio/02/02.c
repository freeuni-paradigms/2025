#include <stdio.h>


// c++ namespaces - std
// using namespace std;
// std::cout <<
//      cin >>
// operator overloading

// 00000000 00000000 00000000 00001001
// 00000000 00000000 00000000 00000001
// 00000000 00000000 00000000 00000010
// 00000000 00000000 00000000 00001000

// 00000000 00000000 00000000 00000001
// 00000000 00000000 00000000 00000001
// && logical and
// || logical or
// & bitwise and
// | bitwise or
// << bitwise left shift
// >>         right shift
// 0110 << 1 == 1100
//      << 1 == 1000
// 0110 >> 1 == 0011
//      >> 1 == 0001
// k & (1 << i)
// 5 + 2 * 2 == 9
// ^ xor
// 0^0 == 0
// 1^1 == 0
// 0^1 1^0 == 1
// ! true -> false
//   false -> true
// ~ 0 -> 1   1 -> 0

// 2s complement
// 0110 6
// 1001
// 
// 1010 -6
// 0000

int negate(int x) {
  return ~x + 1;
}


int main(int argc, char** argv) {
  /* int i = 9; */
  /* for (int j = 7; j >= 0; j--) { */
  /* 	if ((i & (1 << j)) > 0) { */
  /* 	  printf("1"); */
  /* 	} else { */
  /* 	  printf("0"); */
  /* 	} */
  /* } */
  /* printf("\n"); */
  printf("%d\n", negate(6));
  printf("%d\n", negate(-6));
  int i = 10;
  int j = &i; // int*
  int* k = &i;
  
  printf("%d %d %d\n", i, j, *(char*)k);
  return 0;
}

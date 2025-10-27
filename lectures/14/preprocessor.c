// PREPROCESSOR - token search and replace - turing complete
//  c -> c
// c++ template engine - turing complete
// TRANSLATOR
//  c -> object .o
//  -c
// LINKER
//  .o ... .o -> executable

// #include <stdio.h>

A.h -> B.h -> C.h -> A.h
//    -> D.h -> C.h



#define WIDTH 100
#define HEIGHT 20

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int printf(....);

int main(int argc, char** argv) {
  int x = 5;
  int y = 7;
  int k = MAX(x++, y++);
  // x++ > y++ ? x++ : y++
  // x++ ++x
  printf("%d %d %d\n", k, x, y);
  return 0;
}

/*   printf("WIDTH: %d height: %d\n", WIDTH, HEIGHT); */
/*   /\* printf("WIDTH: %d height: %d\n", 100, 20); *\/ */
  
/*   int area = WIDTH * HEIGHT; */
/*   // int area = 100 * 20; */
/*   /\* printf("area: %d\n", area); *\/ */
/*   /\* printf("%d\n", MAX(5, 7)); *\/ */
/*   // printf("%d\n", 5 > 7 ? 5 : 7); */
/*   // MAX(5, "hello"); -> 5 > "hello" ? 5 : "hello" */
/*   printf("%d\n", 10 * MAX(5, 7)); */
/*   printf("%d\n", MAX(1 + 4, 3 - 2)); */
/*   // 1 + 4 > 3 - 0 ? 1 + 4 : 3 + 3 */
/*   // 10 * (5 > 7 ? 5 : 7) ternary operation */
/*   /\* MAX(fact(100), fib(1000)) *\/ */
/*   /\* 	fact(100) > fib(1000) ? fact(100) : fib(1000) *\/ */
/*   return 0; */
/* } */


/* // max */
/* //  braces */
/* //  int + str */
/* //  func calls */
/* //  a++, b++ */
/* // */
/* // assert */
/* //  (cond) ? ((void)0) : exit(1) */
/* //  ifdef ndebug */

/* // includes */
/* // gcc -E */

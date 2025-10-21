#include <stdio.h>

int fibonacci (int i) {
   if (i <= 1) return i;
   int fib1 = fibonacci(i - 1);
   int fib2 = fibonacci(i - 2);
 
   return fib1 + fib2;
}

int main() {
 int i = fibonacci(3);
 printf("%d\n", i);
}

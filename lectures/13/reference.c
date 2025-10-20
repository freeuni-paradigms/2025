#include <stdio.h>


/* struct Foo { */
/*   ...a */
/*    .. */

/*   .. */
/* 	}; */

/* void bar(const Foo* f) { */
/*   * */
/* } */

int main(int argc, char** argv) {
  int x = 5;
  int y = 7;
  int& z = x;
  printf("x: %d   y: %d   z: %d\n", x, y, z);
  z = 10;
  printf("x: %d  y: %d   z: %d\n", x, y, z);
  z = y;
  printf("x: %d   y: %d   z: %d\n", x, y, z);
  z = 20;
  printf("x: %d  y: %d   z: %d\n", x, y, z);
  return 0;
}


class Fraction {
 public:
  void reduce() {
	this
  }

 private:
  static int gcd(int x, int y) {
	...
  }
};

int gcd(...) {
}


Fraction f;
f.reduce(...);


f.gcd(4, 8)

Fraction::gcd(4, 8)

Fraction::reduce(&f, ...)


class Math {
  static
   
}

Math.min(1, 2)

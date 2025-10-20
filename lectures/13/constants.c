// PREPROCESSOR - token search and replace
// TRANSLATOR
// LINKER

// #include <stdio.h>
...
...
...

#define WIDTH 100
#define HEIGHT 20

int main(int argc, char** argv) {
  //printf("WIDTH: %d height: %d\n", WIDTH, HEIGHT);
  printf("WIDTH: %d height: %d\n", 100, 200);
  
  // int area = WIDTH * HEIGHT;
    int area = 100 * 20;
  printf("area: %d\n", area);
  return 0;
}

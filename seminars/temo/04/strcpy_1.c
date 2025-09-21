#include <stdio.h>

void _strcpy(char *dest, const char* src) {
  int i = 0;

  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  dest[i] = '\0';
}

int main() {
  const char *src = "paradigms";

  char dest[5];


  _strcpy(dest, src);

  printf("dest = %s\nsrc= %s\n", dest, src);

  return 0;
}

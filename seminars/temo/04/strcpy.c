#include <stdio.h>
#include <string.h>

void _strcpy(char *dest, const char *src) {
  int i = 0;
  for (; src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
}

int main() {
  const char * src = "QWERY";

  char dest[10] = {65, 65, 65, 65, 65, 65, 65, 65, 65};

  _strcpy(dest, src);

  printf("src = %s\ndest = %s\nsrc len = %d\ndest len = %d", src, dest, strlen(src), strlen(dest));

  return 0;
}

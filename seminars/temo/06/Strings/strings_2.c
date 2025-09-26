#include <stdio.h>
#include <stdlib.h>

int strcmp(const char *s1, const char *s2) {
  int i = 0;
  int cmp = 0;
  int visited = 0;
  while (s1[i] != '\0' || s2[i] != '\0') {
    if (s1[i] == '\0') {
      return -1;
    }
    if (s2[i] == '\0') {
      return 1;
    }
    if (s1[i] != s2[i] && !visited) {
      visited = 1;
      cmp = s1[i] - s2[i];
    }
    i++;
  }

  return cmp;
}

//abcd                bbde
//^                   ^ 
//[    0x1044  ]      [   0x1033  ]

char *strcpy(char *dest, const char *src) {   
  int i = 0;

  //      src[i]       
  while (*(src + i) != 0) {
    *(dest + i) = *(src + i);
    i++;
  }

  *(dest + i) = 0;
  return dest;
}

size_t strlen(const char *s) {
  int i = 0;
  while (*(s + i) != 0) {
    i++;
  }

  return i;
}

// "abcdeqwe\0"      "qwe\0"
//  ^^^^^^
char *strcat(char *dest, const char *src) {
  int len = strlen(dest);
  strcpy(dest + len, src);
  return dest;
}

char *strdup(const char *s) {
  char *new = malloc((strlen(s) + 1) * sizeof(char));
  return strcpy(new, s);
}

void *memset(void *s, int c, size_t n) {
  for (int i = 0; i < n; i++) {
    //s[2]
    //int *s 
    //*(s + 2)
    //[----][----][----][----][]
    //^     ^     ^

    *((char *)s + i) = c;
  }

  return s;
}

int main()
{
    // strcmp
    printf("strcmp:\n");
    char *s1 = "abce";
    char *s2 = "abce";
    int strcmpRes = strcmp(s1, s2);
    if (strcmpRes > 0)
    {
        printf("    s1: %s is greater than s2: %s by %d\n", s1, s2, strcmpRes);
    }
    else if (strcmpRes < 0)
    {
        printf("    s1: %s is less than s2: %s by %d\n", s1, s2, strcmpRes);
    }
    else
    {
        printf("    s1: %s is equal to s2: %s\n", s1, s2);
    }
    printf("\n");

    printf("strcmp:\n");
    char *s1_1 = "abcde";
    char *s2_2 = "bcde";
    int strcmpRes_2 = strcmp(s1_1, s2_2);
    if (strcmpRes_2 > 0)
    {
        printf("    s1: %s is greater than s2: %s by %d\n", s1, s2, strcmpRes_2);
    }
    else if (strcmpRes_2 < 0)
    {
        printf("    s1: %s is less than s2: %s by %d\n", s1, s2, strcmpRes_2);
    }
    else
    {
        printf("    s1: %s is equal to s2: %s\n", s1_1, s2_2);
    }
    printf("\n");

    // strcpy
    printf("strcpy:\n");
    char buffer[50];
    char *strToCopy = "abcde";
    printf("    function returns: %s\n", strcpy(buffer, strToCopy));
    printf("    buffer string after function call: %s\n", buffer);
    printf("\n");

    // strlen
    printf("strlen:\n");
    char *s3 = "Programming";
    char *s4 = "Paradigms";
    const char *s5 = "";
    const char *s6 = "Para\0digms";
    printf("    s3: %s len is %zu\n", s3, strlen(s3));
    printf("    s4: %s len is %zu\n", s4, strlen(s4));
    printf("    s5: %s len is %zu\n", s5, strlen(s5));
    printf("    s6: %s len is %zu\n", s6, strlen(s6));

    printf("\n");

    // strcat
    printf("strcat:\n");
    char buffer2[50];
    strcpy(buffer2, "Start ");

    printf("    function returns: %s\n", strcat(buffer2, "First"));
    printf("    function returns: %s\n", strcat(buffer2, " Second"));
    printf("    function returns: %s\n", strcat(buffer2, " Third"));
    printf("    buffer2 after function calls: %s\n", buffer2);
    printf("\n");

    // strdup
    printf("strdup:\n");
    char *originStr = "Strdup First Example";
    char *newStr = strdup("Strdup First Example");
    printf("    newStr: %s\n", newStr);
    printf("    originStr value address is %p\n", (void *)originStr);
    printf("    newStr value address is %p\n", (void *)newStr);
    printf("\n");

    // memset
    printf("memset:\n");
    char memsetBuffer[50];
    memset((void *)memsetBuffer, 'A', 40);
    printf("    buffer after memset call: %s\n", memsetBuffer);
}

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void Decompress(char **data) {
  // [casdasd\0]
  // ^           char *s      char *decompressed
  // char **data        ^          ^

  char *compressed = *data;
  int i = 0;

  char *decompressed = malloc(1);
  *decompressed = 0;
  int log_len = 1;

  // [****|----] [len * --------] [****|----] [ str  ] ...
  //   len   run             str  ^
  // ^
  // i                            i + 1 + len
  // 00000000 00000000 00000000 ****|----
  // len = 00000000 00000000 00000000 0000|****
  // run = 00000000 00000000 00000000 ****|----
  while (compressed[i] != '\0') {
    unsigned char len_run = (unsigned char) compressed[i]; 
    char len = (len_run >> 4);
    char run = len_run & 0b00001111;

    printf("len = %d\nrun = %d", len, run);
    // str (len სიგრძის სტრინგი) უნდა გადავაკოპიროთ decompressed-ში run-jer
    log_len += len * run;
    decompressed = realloc(decompressed, log_len * sizeof(char));
    
    for (int j = 0; j  < run; j++) {
      strncat(decompressed, compressed + i + 1, len);
    }

    i += len + 1;
  }

  *data = decompressed; 
}

void Test1()
{
    printf("Test1: ");
    char *expectValue = "aabcbcbcx";
    char *data = malloc(8);
    char *ptr = data;

    // 00010010|a|00100011|b|c|00010001|x
    *ptr = (1 << 4) + (1 << 1); // 00010010
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = (1 << 5) + (1 << 1) + 1; // 00100011
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'c';
    ptr++;
    *ptr = (1 << 4) + 1; // 00010001
    ptr++;
    *ptr = 'x';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

void Test2()
{
    printf("Test2: ");
    char *expectValue = "yfoofoobar";
    char *data = malloc(11);
    char *ptr = data;

    // 00010001|y|00110010|f|o|o|00110001|b|a|r
    *ptr = (1 << 4) + 1; // 00010001
    ptr++;
    *ptr = 'y';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + (1 << 1); // 00110010
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + 1; // 00110001
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = 'r';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

void Test3()
{
    printf("Test3: ");
    char *expectValue = "abcdefghfoofoo";
    char *data = malloc(14);
    char *ptr = data;

    // 10000001|a|b|c|d|e|f|g|h|00110010|f|o|o
    *ptr = (1 << 7) + 1; // 10000001
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'c';
    ptr++;
    *ptr = 'd';
    ptr++;
    *ptr = 'e';
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'g';
    ptr++;
    *ptr = 'h';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + (1 << 1); // 00110010
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void Decompress(char **data)
{
    int alloc_size = 1;
    char *decompressed = malloc(alloc_size);
    decompressed[0] = '\0';

    for (int i = 0; (*data)[i] != '\0'; i++)
    {
        int num_chars = ((*data)[i] >> 4) & 0x0f; // [xxxx]xxxx
        int repeats = (*data)[i] & 0x0f; // xxxx[xxxx] -> 15 = 0x0f = 0b00001111

        alloc_size += num_chars * repeats;
        decompressed = realloc(decompressed, alloc_size);

        for (int j = 0; j < repeats; j++)
            strncat(decompressed, *data + i + 1, num_chars);

        i += num_chars;
    }

    free(*data);
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

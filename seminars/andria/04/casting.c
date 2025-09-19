#include <limits.h>
#include <stdio.h>

void print_bits(int num, int num_bits)
{
    for (int bit = 0; bit < num_bits; bit++)
    {
        printf("%i", (num >> (num_bits - bit - 1)) & 0x01);
       
        if (bit % 8 == 7) printf(" ");
    }
    printf("\n");
}

int main()
{
    char ch = 53;
    int a = *(int *)&ch;
    printf("%d - ", a);
    print_bits(a, 32);

    ch = -43;
    printf("%d - ", ch);
    print_bits(ch, 8);
    a = *(int *)&ch;
    printf("%d - ", a);
    print_bits(a, 32);

    // // ******** <- [00000001] 10010000
    ch = 400;
    printf("%d - ", ch);
    print_bits(ch, 8);

    int i = 0b00111110101010011100101001010101;
    float f = (float)i;
    printf("%f\n", f);

    float f_pointer_casted = *(float *)&i;
    printf("%f\n", f_pointer_casted);

    return 0;
}

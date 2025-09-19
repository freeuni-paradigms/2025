#include <string.h>
#include <stdio.h>

void my_strcpy(char * dest, const char *src)
{
    // !!!! strcpy არ ამოწმებს dest-ის ზომას
    // !!!! შესაძლებელია სტრინგების გადაწერა გაცდეს ბაფერის ზომას და სხვა ინფორმაციას გადააწეროს

    int i;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];

    dest[i] = '\0';
}

int main()
{
    char my_str_dest[100], sys_str_dest[100]; // buffers
    char str_src[] = "Chimichurri";

    // დაკოპირებამდე
    printf("my_strcpy: %s\n", my_str_dest);
    printf("strcpy: %s\n", sys_str_dest);

    my_strcpy(my_str_dest, str_src);
    strcpy(sys_str_dest, str_src);

    // დაკოპირების შემდეგ
    printf("my_strcpy: %s\n", my_str_dest);
    printf("strcpy: %s\n", sys_str_dest);
}
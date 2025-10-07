#include "sorted_set.h"
#include <stdio.h>

int cmpfn(const void *aPtr, const void *bPtr)
{
    int a = *(int *)aPtr;
    int b = *(int *)bPtr;
    
    return a - b;
}

int main()
{
    // sortedset set;
    sortedset *set = malloc(sizeof(sortedset));

    SetNew(set, sizeof(int), &cmpfn);
    int a = 21;
    int b = 0;
    SetAdd(set, &a);
    printf("Length: %d\n", set->logSize);
    void *result = SetSearch(set, &b);
    if (result == NULL)
        printf("Elem not found \n");

    int *newResult = (int *)SetSearch(set, &a);
    printf("Element: %d\n", *newResult);
}
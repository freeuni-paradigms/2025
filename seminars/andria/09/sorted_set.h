#ifndef _SORTED_SET_H_
#define _SORTED_SET_H_

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    void *memory;
    int elemSize;
    int (*cmpfn)(const void *, const void *);

    int allocSize, logSize;
} sortedset;

void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *));
bool SetAdd(sortedset *set, const void *elemPtr);
void *SetSearch(sortedset *set, const void *elemPtr);

#endif
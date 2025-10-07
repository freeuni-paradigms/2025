#include "sorted_set.h"
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE(elemSize) ((elemSize + 2 * sizeof(int)))

// typedef struct
// {
//     void *memory;
//     int (*cmpfn)(const void *, const void *);
//     size_t allocSize;
//     size_t logSize;
//     int elemSize;
// } sortedset;

/*
 * Function: SetNew
 * Usage: SetNew(&stringSet, sizeof(char *), StringPtrCompare);
 *        SetNew(&constellations, sizeof(pointT), DistanceCompare);
 * ----------------
 * SetNew allocates the requisite space needed to manage what
 * will initially be an empty sorted set.  More specifically, the
 * routine allocates space to hold up to 'kInitialCapacity' (currently 4)
 * client elements.
 */
static const int kInitialCapacity = 4;
void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *))
{
    set->elemSize = elemSize;
    set->allocSize = kInitialCapacity;
    set->cmpfn = cmpfn;
    set->logSize = 0;

    set->memory = malloc(set->allocSize * BLOCK_SIZE(set->elemSize));
}

/*
 * Function: SetSearch
 * Usage: if (SetSearch(&staffSet, &lecturer) == NULL)
 *            printf("musta been fired");
 * -------------------
 * SetSearch searches for the specified client element according
 * the whatever comparison function was provided at the time the
 * set was created. A pointer to the matching element is returned
 * for successful searches, and NULL is returned to denote failure.
 */
void *SetSearch(sortedset *set, const void *elemPtr)
{
    if (set->logSize == 0) return NULL;

    int index = 0;
    while (true)
    {
        void *localElem = set->memory + index * BLOCK_SIZE(set->elemSize);
        int cmpResult = set->cmpfn(elemPtr, localElem);

        if (cmpResult == 0) return localElem;

        int *index_ptr = (int *)((char *)localElem + set->elemSize);
        if (cmpResult > 0) index_ptr += 1;

        index = *index_ptr;

        if (index == -1) break;
    }

    return NULL;
}

void SetAddOnIndex(sortedset *set, const void *elemPtr, int index)
{
    void *localElem = set->memory + index * BLOCK_SIZE(set->elemSize);
    memmove(localElem, elemPtr, set->elemSize);
    int *index_ptr = (int *)((char *)localElem + set->elemSize);
    *index_ptr = -1;
    *(index_ptr + 1) = -1;
}

/*
 * Function: SetAdd
 * Usage: if (!SetAdd(&friendsSet, &name)) free(name);
 * ----------------
 * Adds the specified element to the set if not already present.  If
 * present, the client element is not copied into the set.  true
 * is returned if and only if the element at address elemPtr
 * was copied into the set.
 */
bool SetAdd(sortedset *set, const void *elemPtr)
{
    if (set->logSize == 0) 
    {
        SetAddOnIndex(set, elemPtr, set->logSize++);
        return true;
    }

    int index = 0;
    while (true)
    {
        void *localElem = set->memory + index * BLOCK_SIZE(set->elemSize);
        int cmpResult = set->cmpfn(elemPtr, localElem);

        if (cmpResult == 0) break;

        int *index_ptr = (int *)((char *)localElem + set->elemSize);
        if (cmpResult > 0) index_ptr += 1;

        index = *index_ptr;

        if (index == -1)
        {
            if (set->allocSize == set->logSize)
            {
                set->allocSize *= 2;
                set->memory = realloc(set->memory, set->allocSize);
            }

            *index_ptr = set->logSize;
            SetAddOnIndex(set, elemPtr, set->logSize++);

            return true;
        }
    }

    return false;
}
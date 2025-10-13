#include "sorted_set.h"
#include <string.h>
#include <stdlib.h>

// typedef struct { 
//   void *base;
//   int elemSize;
//   int allocLen;
//   int logLen;
//   int (*cmpfn)(const void *, const void *);
// } sortedset;

#define MEMORY_SIZE(capacity, elemSize) (capacity * (elemSize + 2*sizeof(int)) + sizeof(int))
#define ELEM_PTR(base, index, elemSize) (char *)base + sizeof(int) + index * (2 * sizeof(int) + elemSize)

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
void SetNew(sortedset *set, int elemSize,
            int (*cmpfn)(const void *, const void *)) {
  set->base = malloc(MEMORY_SIZE(kInitialCapacity, elemSize));
  *(int *)set->base = -1;
  set->elemSize = elemSize;
  set->allocLen = kInitialCapacity;
  set->logLen = 0;
  set->cmpfn = cmpfn;
}

int *findElem(sortedset *set, const void *elemPtr) {
  int *indexPtr = (int *)set->base;
  void *currentElem = NULL;
  
  while (*indexPtr != -1) {
    currentElem = ELEM_PTR(set->base, *indexPtr, set->elemSize);
    int res = set->cmpfn(elemPtr, currentElem); 
  
    if (res == 0) {
      return indexPtr;
    }

    if (res < 0) {
      indexPtr = (int *)((char *)currentElem + set->elemSize); 
    } else {
      indexPtr = (int *)((char *)currentElem + set->elemSize + sizeof(int));
    }
  }
  return indexPtr;
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
void *SetSearch(sortedset *set, const void *elemPtr) {
  int *indexPtr = findElem(set, elemPtr);
  int index = *indexPtr;

  if (index == -1) {
    return NULL;
  }

  return ELEM_PTR(set->base, index, set->elemSize); 
}

/*
 * Function: SetAdd
 * Usage: if (!SetAdd(&friendsSet, &name)) free(name);
 * ----------------
 * Adds the specified element to the set if not already present.  If
 * present, the client element is not copied
 into the set.  true
 * is returned if and only if the element at address elemPtr
 * was copied into the set.
 */
bool SetAdd(sortedset *set, const void *elemPtr) {
  int *indexPtr = findElem(set, elemPtr);

  if (*indexPtr != -1) {
    return false;
  }

  if (set->logLen == set->allocLen) {
    set->allocLen *= 2;
    set->base = realloc(set->base, MEMORY_SIZE(set->allocLen, set->elemSize));
  }

  int index = set->logLen;
  *indexPtr = index;

  void *newElem = ELEM_PTR(set->base, index, set->elemSize);
  memcpy(newElem, elemPtr, set->elemSize);

  int *indices = (int *)((char *)newElem + set->elemSize);
  indices[0] = indices[1] = -1;

  set->logLen++;
  return true;
}

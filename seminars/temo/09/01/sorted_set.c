#include "sorted_set.h"
#include <string.h>
#include <stdlib.h>

// typedef struct { 
//   void *base;
//   int elemSize;
//   int logLen;
//   int allocLen;
//   int (*cmpfn)(const void *, const void *);
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

#define MEMORY_SIZE(capacity, elemSize) (sizeof(int) + capacity * (elemSize + 2 * sizeof(int)))
#define ELEM_PTR(base, index, elemSize) ((char *)base + sizeof(int) + index * (elemSize + 2 * sizeof(int)))

static const int kInitialCapacity = 4; 
void SetNew(sortedset *set, int elemSize,  
            int (*cmpfn)(const void *, const void *)) {
  set->base = malloc(MEMORY_SIZE(kInitialCapacity, elemSize));
  set->elemSize = elemSize;
  set->logLen = 0;
  set->allocLen = kInitialCapacity;
  set->cmpfn = cmpfn;

  *(int *)(set->base) = -1;
}

int *findIndex(sortedset *set, const void *elemPtr) {
  void *currentElem = (int*)set->base + 1;
  int *indexPtr = set->base;

  while (*indexPtr != -1) {
    int res = set->cmpfn(elemPtr, currentElem);
    
    if (res == 0) {
      return indexPtr;
    }

    if (res < 0) {
      indexPtr = (int *)((char *)currentElem + set->elemSize);
    }

    if (res > 0) {
      indexPtr = (int *)((char *)currentElem + set->elemSize + sizeof(int));
    }
    
    currentElem = ELEM_PTR(set->base, *indexPtr, set->elemSize);
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
  int *indexPtr = findIndex(set, elemPtr);
  int index = *indexPtr;

  if  (index == -1) {
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
  int *indexPtr = findIndex(set, elemPtr);

  if (*indexPtr != -1) {
    return false;
  }
  
  if (set->allocLen == set->logLen) {
    set->allocLen *= 2;
    set->base = realloc(set->base, MEMORY_SIZE(set->allocLen, set->elemSize));
  }

  int newIndex = set->logLen;
  *indexPtr = newIndex;

  void *newElemPtr = ELEM_PTR(set->base, newIndex, set->elemSize);
  memcpy(newElemPtr, elemPtr, set->elemSize);
  int *indices = (int *)((char *)newElemPtr + set->elemSize);
  
  set->logLen++;
  *indices = -1;
  *(indices + 1) = -1;
  return true;
}

#include "sorted_set_.h"
// typedef struct { 
//   void *base;
//   int elemSize;
//   int allocLen;
//   int logLen;
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
static const int kInitialCapacity = 4;
void SetNew(sortedset *set, int elemSize,
            int (*cmpfn)(const void *, const void *)) {
  set->base = malloc(kInitialCapacity * (elemSize + 2 * sizeof(int)) + sizeof(int));
  *(int *)set->base = -1;
  set->elemSize = elemSize;
  set->allocLen = kInitialCapacity;
  set->logLen = 0;
  set->cmpfn = cmpfn;
}

int *findElem(sortedset *set, const void *elemPtr) {

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
  void *elem = (char *)set->base + sizeof(int) + index * (set->elemSize + 2 * sizeof(int));
  return elem;
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

  *indexPtr = set->logLen;

  if (set->logLen >= set->allocLen) {
    set->allocLen *= 2;
    set->base = realloc(set->allocLen * (elemSize + 2 * sizeof(int)) + sizeof(int));
  }
  
  void *newElemAddr = (char *)set->base + sizeof(int) + set->logLen * (set->elemSize + 2 * sizeof(int));

  memcpy(newElemAddr, elemPtr, elemSize);
  
  (int *)((char *)newElemAddress + elemSize)[0] = -1;
  (int *)((char *)newElemAddress + elemSize)[1] = -1;
  
  set->logLen++;
}

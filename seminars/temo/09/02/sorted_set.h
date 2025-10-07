typedef struct { 
  void *base;
  int elemSize;
  int allocLen;
  int logLen;
  int (*cmpfn)(const void *, const void *);
} sortedset;

void SetNew(sortedset *set, int elemSize,  
            int (*cmpfn)(const void *, const void *)); 

bool SetAdd(sortedset *set, const void *elemPtr); 

void *SetSearch(sortedset *set, const void *elemPtr);

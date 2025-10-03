// API - contract

typedef void(*FreeFn)(void*);

typedef struct {
  void* base;
  int elem_size;
  int log_len;
  int alloc_len;
  FreeFn free_fn;
} Stack;

// Call by value

void StackInit(Stack* s, int elem_size, FreeFn free_fn);
void StackDestroy(Stack* s);
// Takes ownership of the given memory.
void StackPush(Stack* s, void* v);
// !! Gives ownership of the returned memory to the client.
void StackPop(Stack* s, void* addr);
int StackSize(Stack* s);

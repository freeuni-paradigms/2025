typedef struct {
  int* base;
  int log_len;
  int alloc_len;
} Stack;

// Call by value

void StackInit(Stack* s);
void StackDestroy(Stack* s);
void StackPush(Stack* s, int v);
int StackPop(Stack* s);

Arena
Utilization

10 20 50
10 .20. 50 .20.
malloc(30) -> NULL
CPU cache
10 50 .40.
defragmentation - hard disk
paused


void* x = malloc(10); // 0

...
...

void* y = ... // malloc(50); // 30


MacOS
Handle - void* -> void**

Malloc/Free
NewHandle/DestroyHandle
HandleLock 
HandleUnlock


Function argument + local variables -> Stack


Struct -> Activation Record
Function -> Stack Frame

// 9 
void A(int a, int b) {
  bool x;
  ...
  
}

// 20
void B(double d, char* c) {
  int i;
  ...
  A();
  if (1 == 0) {
    ...
	int j;
	...
  }
  ...
}

// 52
void C() {
  int a[10];
  char* str;
  B();
  Fraction f;
}


int main() {
  // C();
}

void foo() {
cin >> n;
int a[n]; // int* a = malloc(sizeof(int) * n);
}


javascript -> tree shaking -- dead code

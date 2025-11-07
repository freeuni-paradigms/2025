// MAX

int max(int a) {
  short x = a;
  short y = *(((short*)&a) + 1);
  if (x > y) {
	  return x;
  } else {
	  return y;
  }
}

// PROCESS

typedef struct {
  double d;
  char c[4];
  int i;
} Work;

typedef int(*TransformFN)(int);

int process(int n, Work* w, TransformFN tfn) {
  int ret = 0;
  int i = 0;
  while (i < n) {
	    ret += tfn(*(int*)((short*)w[i].c + 1));
	    i += 2;
  }
  return ret;
}

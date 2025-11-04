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
  while (true) {
	i += 2;
	if (i == n) {
	  break;
	}
	ret += tfn(*(int*)((short*)w[i].c + 1));
  }
  return ret;
}

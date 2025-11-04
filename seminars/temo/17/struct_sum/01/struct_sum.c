typedef struct {
  char c;
  short s[2];
  int i;
} Data;

typedef void (*PopulateFn)(int num, Data *d);

int StructSum(int num, PopulateFn popFn) {
  Data d;
  popFn(num, &d);
  return d.c + d.s[0] + d.s[0] + d.s[1] + d.i;
}

/////////////////// TESTS BEGIN ///////////////////

void ecall(int, int);
void populate_threes(int num, Data *d) {
  d->c = 3 + num;
  d->s[0] = 3 + num;
  d->s[1] = 3 + num;
  d->i = 3 + num;
  return;
}
void populate_2pows(int num, Data *d) {
  d->c = 2 + num;
  d->s[0] = 4 + num;
  d->s[1] = 8 + num;
  d->i = 16 + num;
  return;
}

#define run_test(test_name, num, sum, popFn)                                   \
  {                                                                            \
    int res = StructSum(num, popFn);                                           \
    ecall(4, (long)test_name);                                                 \
    ecall(1, res == sum);                                                      \
    ecall(11, '\n');                                                           \
  }

int main(int argc, char **argv) {
  run_test("[TEST #1] StructSum( 0, fill_with_threes)  result=\0", 0, 15,
           populate_threes);
  run_test("[TEST #2] StructSum( 1, fill_with_threes)  result=\0", 1, 20,
           populate_threes);
  run_test("[TEST #3] StructSum(-1, fill_with_threes)  result=\0", -1, 10,
           populate_threes);

  run_test("[TEST #4] StructSum( 0, fill_with_2pows)   result=\0", 0, 34,
           populate_2pows);
  run_test("[TEST #5] StructSum( 1, fill_with_2pows)   result=\0", 1, 39,
           populate_2pows);
  run_test("[TEST #6] StructSum(-1, fill_with_2pows)   result=\0", -1, 29,
           populate_2pows);
}

/////////////////// TESTS END ///////////////////

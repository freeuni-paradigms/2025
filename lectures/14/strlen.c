// int strlen(int*);

int main() {
  int num = 100;
  int k = strlen(&num);
  printf("%d\n", k);
  return 0;
}

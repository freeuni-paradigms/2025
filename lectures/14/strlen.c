// int strlen(int*);

// int memcmp(void*, void*, int);
// int memcmp(int*);

int main() {
  int num = 100;
  int k = memcmp(&num);
  printf("%d\n", k);
  return 0;
}

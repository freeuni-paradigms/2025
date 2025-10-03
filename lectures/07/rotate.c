/* 123456 */
/* 561234 */



/* 561234 */

/* 56 */

void rotate(void* start, void* middle, void* end) {
  int left = (char*)middle - (char*)start;
  int right = (char*)end - (char*)middle;
  void* tmp = malloc(right);
  assert(tmp != NULL);
  memcpy(tmp, (char*)start + left, right);
  memmove((char*)start + right, start, left);
  memcpy(start, tmp, right);
  free(tmp);
}

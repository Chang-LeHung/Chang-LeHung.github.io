
#include <stdio.h>

int main() {
  int i = 10;
  int size = __builtin_popcount(i);
  printf("size = %d\n", size);
  return 0;
}
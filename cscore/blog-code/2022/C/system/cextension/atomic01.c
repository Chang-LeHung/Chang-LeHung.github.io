

#include <stdio.h>

int main() {
  int i = 0;
  // __sync_fetch_and_add(&i, 1);
  // asm volatile(
  //   "subl $1, %0;"
  //   :"+r"(i)::
  // );
  printf("i = %d\n", i);
  return 0;
}
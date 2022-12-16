
#include <stdio.h>

#define likely(x) __builtin_expect (!!(x), 1)
#define unlikely(x) __builtin_expect (!!(x), 0)


int main() {
  int r = 1;
  if(likely(r)) {
    printf("aaa\n");
  }
  if(unlikely(r))
    printf("bbb\n");
  return 0;
}
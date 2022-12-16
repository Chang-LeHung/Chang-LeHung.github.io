

#include <stdio.h>

int main()
{
  printf("%d\n", __builtin_ctz(1));
  printf("%d\n", __builtin_ctz(2));
  printf("%d\n", __builtin_ctz(3));
  printf("%d\n", __builtin_ctz(4));
  return 0;
}

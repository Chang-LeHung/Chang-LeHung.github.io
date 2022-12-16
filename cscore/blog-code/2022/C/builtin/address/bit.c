

#include <stdio.h>

#define lowbit(x) (1 << (__builtin_ctz(x)))

int lowbit2(int x)
{
  return (x) & (-x);
}

int main()
{
  // int i = -1;
  // printf("bits = %d\n", __builtin_popcount(i));
  // i = 15;
  // printf("bits = %d\n", __builtin_popcount(i));
  for(int i = 0; i < 16; ++i)
  {
    printf("macro = %d function = %d\n", lowbit(i), lowbit2(i));
  }
  return 0;
}


#include <stdio.h>

int main()
{
  for(int i = 1; i < 16; ++i) 
  {
    printf("i = %2d and result = %2d\n", i, __builtin_clz(i));
  }
  printf("i = %2d and result = %2d\n", -1, __builtin_clz(-1));
  return 0;
}


#include <stdio.h>

int main()
{
  for(int i = 0; i < 100; ++i) 
  {
    printf("i = %d and result = %d\n", i, __builtin_parity(i));
  }
  return 0;
}

#include <stdio.h>

void func_a()
{
  void* p = __builtin_return_address(0);
  printf("fun_a return address = %p\n", p);

  p = __builtin_return_address(1);
  printf("In func_a main return address = %p\n", p);
}


int main()
{
  void* p = __builtin_return_address(0);
  printf("main return address = %p\n", p);
  func_a();
  return 0;
}
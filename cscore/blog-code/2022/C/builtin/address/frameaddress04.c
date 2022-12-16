
#include <stdio.h>

void func_a()
{
  printf("In func_a\n");
  void* p = __builtin_frame_address(2);
  printf("caller frame address = %p\n", p);
}

void func_b()
{
  printf("In func_b\n");
  void* p = __builtin_frame_address(1);
  printf("caller frame address = %p\n", p);

  func_a();
}


int main()
{
  void* p = __builtin_frame_address(0);
  printf("main frame address = %p\n", p);
  func_b();
  return 0;
}
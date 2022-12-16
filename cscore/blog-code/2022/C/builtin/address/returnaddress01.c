
#include <stdio.h>
#include <sys/types.h>

#define return_address            \
    u_int64_t rbp;                \
    asm volatile(                 \
      "movq %%rbp, %0":"=m"(rbp)::\
    );                            \
    printf("From inline assembly return address = %p\n", (u_int64_t*)*(u_int64_t*)(rbp + 8));

void func_a()
{
  printf("In func_a\n");
  void* p = __builtin_return_address(0);
  printf("fun_a return address = %p\n", p);
  return_address
}

int main()
{
  printf("In main function\n");
  void* p = __builtin_return_address(0);
  printf("main return address = %p\n", p);
  return_address
  func_a();
  return 0;
}
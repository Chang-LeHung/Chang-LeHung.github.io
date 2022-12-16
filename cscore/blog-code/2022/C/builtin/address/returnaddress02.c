

#include <stdio.h>
#include <sys/types.h>

#define return_address            \
    u_int64_t rbp;                \
    asm volatile(                 \
      "movq %%rbp, %%rcx;"        \
      "movq (%%rcx), %%rcx;"      \
      "movq %%rcx, %0;"           \
      :"=m"(rbp)::"rcx"           \
    );                            \
    printf("From inline assembly main return address = %p\n", (u_int64_t*)*(u_int64_t*)(rbp + 8));

void func_a()
{
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> In func_a\n");
  void* p = __builtin_return_address(1);
  printf("main return address = %p\n", p);
  return_address
  printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Out func_a\n");
}


int main()
{
  func_a();
  void* p = __builtin_return_address(0);
  printf("main function return address = %p\n", p);
  return 0;
}


#include <stdio.h>
#include <sys/types.h>

u_int64_t rbp;

#define frame_address                   \
        asm volatile(                   \
          "movq %%rbp, %0;"             \
          :"=m"(rbp)::                  \
        );                              \
        printf("rbp = %p from inline assembly\n", (void*) rbp);

void bar()
{
  void* rbp = __builtin_frame_address(0);
  printf("rbp = %p\n", rbp);
  frame_address
}

int main()
{
  bar();
  return 0;
}
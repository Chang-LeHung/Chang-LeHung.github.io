

#include <stdio.h>
#include <sys/types.h>

static
inline void func()
{
    u_int64_t rbp;                
    asm volatile(                 
      "movq %%rbp, %0":"=m"(rbp)::
    );                            
    printf("From inline assembly return address = %p\n", (u_int64_t*)*(u_int64_t*)(rbp + 8));
}

int main()
{
  printf("main = %p\n", main);
  printf("func = %p\n", func);
  func();
  return 0;
}


#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>

void sig(int si)
{
  uint64_t rsp, rbp;
  asm volatile(
    "movq %%rsp, %0;"
    "movq %%rbp, %1"
    :"=m"(rsp), "=m"(rbp)::
  );
  printf("sig: rsp = %p rbp = %p\n", (void*)rsp, (void*)rbp);
}

int main()
{
  signal(SIGINT, sig);
  uint64_t rsp, rbp;
  asm volatile(
    "movq %%rsp, %0;"
    "movq %%rbp, %1"
    :"=m"(rsp), "=m"(rbp)::
  );
  printf("rsp = %p rbp = %p\n", (void*)rsp, (void*)rbp);
  sleep(4);
  return 0;
}
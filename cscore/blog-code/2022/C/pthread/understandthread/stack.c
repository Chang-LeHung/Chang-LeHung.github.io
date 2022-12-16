
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

u_int64_t rsp;
u_int64_t rbp;
u_int64_t rip;

void find_rip() {
  asm volatile(
    "movq 8(%%rbp), %0;"
    :"=r"(rip)::
  );
}

void* func(void* arg) {
  printf("In func\n");
  asm volatile(             \
    "movq %%rsp, %0;"       \
    "movq %%rbp, %1;"       \
    :"=m"(rsp), "=m"(rbp):: \
  );
  find_rip();
  printf("stack frame: rsp = %p rbp = %p rip = %p\n", (void*)rsp, (void*)rbp, (void*) rip);
  return NULL;
}

int main() {
  printf("================\n");
  printf("In main\n");
  asm volatile(             \
    "movq %%rsp, %0;"       \
    "movq %%rbp, %1;"       \
    :"=m"(rsp), "=m"(rbp):: \
  );
  find_rip();
  printf("stack frame: rsp = %p rbp = %p rip = %p\n", (void*)rsp, (void*)rbp, (void*) rip);
  printf("================\n");
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  pthread_join(t, NULL);
  return 0;
}

// https://stackoverflow.com/questions/12397451/why-cant-i-save-the-value-of-rip

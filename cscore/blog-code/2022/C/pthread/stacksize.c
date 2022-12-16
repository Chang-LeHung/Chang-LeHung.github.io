

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int times = 1;
u_int64_t rbp;

void* func(void* arg) {
  #if __X86__
      asm volatile(
      "movq %%rbp, %0;"
      :"=m"(rbp)::
    );
    printf("times = %d rbp = %lx\n", times, rbp);
  #else
    printf("times = %d\n", times);
  #endif
  times++;
  char s[1 << 20];
  func(NULL);
  return NULL;
}

int main() {
  setbuf(stdout, NULL);
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  pthread_join(t, NULL);
  // func(NULL);
  return 0;
}
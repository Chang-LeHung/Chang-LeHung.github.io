
#include <stdio.h>
#include <omp.h>
#include <stdint.h>

uint64_t rsp, rbp;


int fib(int n) {
  asm volatile(             \
    "movq %%rsp, %0;"       \
    "movq %%rbp, %1;"       \
    :"=m"(rsp), "=m"(rbp):: \
  );
  printf("Start : n = %d tid = %d rbp = %p rsp = %p\n", n, omp_get_thread_num(), (void*)rbp, (void*)rsp);
  int x, y, r;
  if (n < 2)
    r =  n;
  else {
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);
    #pragma omp taskwait
    r = x + y;
  }
  asm volatile(             \
    "movq %%rsp, %0;"       \
    "movq %%rbp, %1;"       \
    :"=m"(rsp), "=m"(rbp):: \
  );
  printf("End : n = %d tid = %d rbp = %p rsp = %p\n", n, omp_get_thread_num(), (void*)rbp, (void*)rsp);
  return r;
}

int main() {

  #pragma omp parallel num_threads(1)
  {
    int x = fib(3);
    printf("x = %d\n", x);
  }
  return 0;
}
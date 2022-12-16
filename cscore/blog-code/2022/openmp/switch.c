

#include <stdio.h>
#include <omp.h>
#include <stdint.h>
#include <unistd.h>

uint64_t rsp, rbp;
#define COLOR_NORMAL "\033[0m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREY "\033[1;30m"
#define STACK_DEBUG printf("tid = %d"COLOR_RED" rsp = %lx"COLOR_NORMAL \
                            COLOR_GREEN" rbp = %lx"COLOR_NORMAL"\n", \
                            omp_get_thread_num(), rsp, rbp);

#define FIND_RSP_RBP \
        asm volatile(\
          "movq %%rbp, %0;"\
          "movq %%rsp, %1;"\
          :"=m"(rbp), "=m"(rsp)::\
        );


int i = 1;
int main() {

  #pragma omp parallel num_threads(1)
  {
    #pragma omp task
    {
      #pragma omp task
      {
        while(i == 1)
        {
          FIND_RSP_RBP
          STACK_DEBUG
          sleep(1);
          #pragma omp taskyield
        }
        printf("task111 has finished\n");
      }

      i = 2;
      printf("task1 has finished\n");
    }

  }

  return 0;
}
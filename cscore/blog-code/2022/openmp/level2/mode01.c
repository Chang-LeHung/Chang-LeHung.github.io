#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <stdint.h>

#define COLOR_NORMAL "\033[0m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREY "\033[1;30m"

#define STACK_DEBUG_WITH_DATA printf("tid = %d"COLOR_RED" rsp = %lx"COLOR_NORMAL \
                            COLOR_GREEN" rbp = %lx"COLOR_YELLOW" data address = %p"COLOR_NORMAL"\n", \
                            omp_get_thread_num(), rsp, rbp, &data);


#define STACK_DEBUG printf("tid = %d"COLOR_RED" rsp = %lx"COLOR_NORMAL \
                            COLOR_GREEN" rbp = %lx"COLOR_NORMAL"\n", \
                            omp_get_thread_num(), rsp, rbp);

#define FIND_RSP_RBP \
        asm volatile(\
          "movq %%rbp, %0;"\
          "movq %%rsp, %1;"\
          :"=m"(rbp), "=m"(rsp)::\
        );

#define HLINE printf("===========================\n");

int gpid;
uint64_t rbp;
uint64_t rsp;

int main() {
  omp_set_num_threads(2);
  #pragma omp parallel
  {
    #pragma omp single
    {
      HLINE
    }
    
    #pragma omp critical
    {
      printf("at the beginning pid = %d\n", omp_get_thread_num());
      FIND_RSP_RBP
      STACK_DEBUG
    }

    #pragma omp barrier
    #pragma omp single
    {
      HLINE
    }
    #pragma omp single
    {

      #pragma omp task
      {
        printf("task 1 pid = %d\n", omp_get_thread_num());
        FIND_RSP_RBP
        STACK_DEBUG
        HLINE
      }

      #pragma omp task shared(gpid)
      {
        printf("task 2 pid = %d\n", omp_get_thread_num());
        FIND_RSP_RBP
        STACK_DEBUG
        HLINE
      }

      #pragma omp task shared(gpid) untied
      {
        printf("task 3 pid = %d\n", omp_get_thread_num());
        FIND_RSP_RBP
        STACK_DEBUG
        int data = 100;
        gpid = omp_get_thread_num();
        while(gpid == omp_get_thread_num() && data >= 95) {
          sleep(1);
          data--;
          printf("pid = %d yield data = %d\n", omp_get_thread_num(), data);
          FIND_RSP_RBP
          STACK_DEBUG
          #pragma omp taskyield
        }
        FIND_RSP_RBP
        STACK_DEBUG
        HLINE
        printf("pid = %d yield data = %d\n", omp_get_thread_num(), data);
      }

      #pragma omp task shared(gpid)
      {
          printf("task 4 pid = %d\n", omp_get_thread_num());
          FIND_RSP_RBP
          STACK_DEBUG
          HLINE
      }
    }
  }
  return 0;
}
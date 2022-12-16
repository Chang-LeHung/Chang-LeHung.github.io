

#include <stdio.h>
#include <omp.h>


int main() {
  printf("Hello World\n");
  omp_set_num_threads(1);

  #pragma omp parallel
  {
    printf("S\n");
    #pragma omp task
    printf("race(tid = %d)\n", omp_get_thread_num());
    printf("Car\n");
  }
  return 0;
}

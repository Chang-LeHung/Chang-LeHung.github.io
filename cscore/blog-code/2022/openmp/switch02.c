

#include <stdio.h>
#include <omp.h>
#include <stdint.h>
#include <unistd.h>

int i = 1;
int main() {

  #pragma omp parallel num_threads(1)
  {
    #pragma omp task
    {
      printf("1\n");
    }
    printf("2\n");
    #pragma omp task
    {
      printf("3\n");
    }
    printf("43\n");
  }

  return 0;
}
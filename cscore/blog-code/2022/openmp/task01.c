


#include <stdio.h>
#include <omp.h>
#include <stdint.h>
#include <unistd.h>

int i = 1;
int main() {
  #pragma omp parallel num_threads(2)
  { 
    printf("Hello World\n");
    #pragma omp task
    {
      printf("Hello World\n");
      #pragma omp task
      {
        printf("Hello World\n");
      }
    }
  }
  return 0;
}

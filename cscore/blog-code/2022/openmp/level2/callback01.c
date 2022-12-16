

#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int turn = 1;

int main() {
  omp_set_num_threads(2);
  #pragma omp parallel
  {
    printf("In tid = %d\n", omp_get_thread_num());
    #pragma omp task untied
    {
      int data = 100;
      printf("In 1st task before taskyield : data = %d\n", data);
      while(turn == 1)
      {
        printf("tid = %d in yield 1\n", omp_get_thread_num());
        sleep(1);
        #pragma omp taskyield
      }
      printf("In 1st task after taskyield : data = %d\n", data);
    }

    #pragma omp task untied
    {
      int data = -100;
      printf("In 2nd task before taskyield : data = %d\n", data);
      while(turn == 2)
      {
        printf("tid = %d in yield 2\n", omp_get_thread_num());
        sleep(1);
        #pragma omp taskyield
      }
      turn = 2;
      printf("In 2nd task after taskyield : data = %d\n", data);
    }
  }
  return 0;
}
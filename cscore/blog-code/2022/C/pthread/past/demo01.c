

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

int main() {
  long n = 1;
  int m = (int)__sync_or_and_fetch(&n, 2);
  __sync_synchronize();
  printf("sizeof(pthread_t) = %ld, sizeof(pid_t) = %ld\n", sizeof(pthread_t), sizeof(pid_t));
  printf("m = %d\n", m);
  return 0;
}
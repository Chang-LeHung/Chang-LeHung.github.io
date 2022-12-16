
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MiB * 1 << 20

int times = 0;
void* stack_overflow(void* args) {
  printf("times = %d\n", ++times);
  char s[1 << 20]; // 1 MiB
  stack_overflow(NULL);
  return NULL;
}

int main() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, 24 MiB);
  pthread_t t;
  pthread_create(&t, &attr, stack_overflow, NULL);
  pthread_join(t, NULL);
  pthread_attr_destroy(&attr);
  return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define KiB * 1 << 10
#define MiB * 1 << 20
#define STACK_SIZE 2 MiB

int times = 0;

static
void* stack_overflow(void* args) {
  printf("times = %d\n", ++times);
  char s[ 2 KiB]; // 1 MiB
  stack_overflow(NULL);
  return NULL;
}

int main() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  void* stack = malloc(32 KiB);
  pthread_t t;
  pthread_attr_setstack(&attr, stack + (16 KiB), 16 KiB);
  pthread_create(&t, &attr, stack_overflow, NULL);
  pthread_join(t, NULL);
  pthread_attr_destroy(&attr);
  free(stack);
  return 0;
}
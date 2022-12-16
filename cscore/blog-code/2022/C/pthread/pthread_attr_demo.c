

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>

int times = 1;
u_int64_t rbp;

void* func(void* arg) {
  printf("times = %d\n", times);
  times++;
  char s[1 << 20];
  func(NULL);
  return NULL;
}

int main() {

  pthread_t t;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  size_t size;
  pthread_attr_getstacksize(&attr, &size);
  printf("default stack size = %lx bytes\n", size);
  pthread_attr_setstacksize(&attr, 1 << 22);
  pthread_create(&t, &attr, func, NULL);
  pthread_join(t, NULL);
  func(NULL);
  pthread_attr_destroy(&attr);
  return 0;
}
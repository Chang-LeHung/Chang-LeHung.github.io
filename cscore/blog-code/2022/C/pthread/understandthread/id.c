
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

void* func(void* arg) {
  printf("pthread id = %ld tid = %d\n", pthread_self(), (int)gettid());
  return NULL;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  pthread_join(t, NULL);
  return 0;
}
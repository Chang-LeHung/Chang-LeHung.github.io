
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void* func(void* args) {
  int i = 0;
  printf("pid = %d tid = %ld\n", getpid(), pthread_self());
  return NULL;
}

void* exit_(void* args) {
  
  printf("pid = %d tid = %ld\n", getpid(), pthread_self());
  return NULL;
}


int main() {
  pthread_attr_t attr;
  printf("main process = %d\n", getpid());
  pthread_t t1, t2;
  pthread_create(&t1, NULL, func, NULL);
  pthread_create(&t2, NULL, exit_, NULL);
  printf("main process tid = %ld of t1\n", *(u_int64_t *)t1);
  printf("main process tid = %ld of t2\n", *(u_int64_t *)t2);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
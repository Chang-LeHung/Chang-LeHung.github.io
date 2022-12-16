
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* arg) {

  pid_t t = getpid();
  printf("tid = %d\n", t);
  return NULL;
}

int main() {
  printf("pid = %d\n", getpid());
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  pthread_join(t, NULL);
  return 0;
}
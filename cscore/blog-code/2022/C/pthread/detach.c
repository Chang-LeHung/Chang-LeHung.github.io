
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg) {
  pthread_detach(pthread_self());
  return NULL;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  // pthread_detach(t);
  sleep(1);
  return 0;
}
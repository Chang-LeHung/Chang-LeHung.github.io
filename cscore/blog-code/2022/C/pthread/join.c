
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* a(void* arg) {
  sleep(1);
  return NULL;
}

void* b(void* arg) {
  while(1);
  return NULL;
}

int main() {

  pthread_t t1, t2;
  pthread_create(&t1, NULL, a, NULL);
  pthread_create(&t2, NULL, b, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
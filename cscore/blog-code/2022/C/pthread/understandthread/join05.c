

#include <stdio.h>
#include <pthread.h>

void* func(void* arg) {
  int i = 0;
  while(i > 100000000) {
    i++;
  }
  return NULL;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);

  pthread_join(t, NULL);
  return 0;
}
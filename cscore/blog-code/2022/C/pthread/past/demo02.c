

#include <stdio.h>
#include <stdatomic.h>
#include <unistd.h>
#include <pthread.h>

int a = 1;
int b = 2;
atomic_int c;

void* func(void* args) {
  sleep(1);
  for(int i = 0; i < 10000; i++) {
     atomic_fetch_add_explicit((&a), b,  memory_order_seq_cst);
  }
  return NULL;
}

int main() {
  pthread_t threads[10];
  for(int i = 0; i < 10; i++) {
    pthread_create(threads + i, NULL, func, NULL);
  }

  for(int i = 0; i < 10; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("a = %d b = %d\n",a ,b);
  return 0;
}


#include <stdio.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void once_func() {
  printf("this is once func tid = %ld\n", (long int)pthread_self());
}

void* func(void* arg) {
  printf("tid = %ld start\n", (long int)pthread_self());
  pthread_once(&once, once_func);  
  printf("tid = %ld end\n", (long int)pthread_self());
  return NULL;
}

int main() {

  pthread_t t1, t2;
  pthread_create(&t1, NULL, func, NULL);
  pthread_create(&t2, NULL, func, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
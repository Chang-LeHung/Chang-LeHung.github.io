

#include <stdio.h>
#include <pthread.h>

void* func(void* arg) {

  printf("线程自己打印线程\tid = %ld\n", pthread_self());

  return NULL;
}

int main() {

  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  printf("主线程打印线程 t 的线程 id = %ld\n", *(long*)(&t));
  printf("主线程打印线程 t 的线程 id = %ld\n", t);
  pthread_join(t, NULL);
  return 0;
}
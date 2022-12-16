
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

void* func(void* arg)
{
  pthread_exit((void*)100);
  return NULL;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  
  void* ret;
  pthread_join(t, &ret);
  printf("ret = %ld\n", (u_int64_t)(ret));
  return 0;
}
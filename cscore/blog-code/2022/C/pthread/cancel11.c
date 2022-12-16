

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void handler1(void* arg)
{
  printf("in handler1 i1 = %d\n", *(int*)arg);
}

void handler2(void* arg)
{
  printf("in handler2 i2 = %d\n", *(int*)arg);
}


void* func(void* arg)
{
  int i1 = 1, i2 = 2;
  pthread_cleanup_push(handler1, &i1);
  pthread_cleanup_push(handler2, &i2);

  printf("In func\n");
  sleep(1);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(1);
  return NULL;
}

int main() 
{
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  pthread_cancel(t);
  void* res;
  pthread_join(t, &res);
  if(res == PTHREAD_CANCELED)
  {
    printf("thread was cancelled\n");
  }
  return 0;
}
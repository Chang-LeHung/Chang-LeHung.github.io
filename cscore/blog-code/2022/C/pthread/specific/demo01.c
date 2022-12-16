


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_key_t key;

void key_destructor1(void* arg) 
{
  printf("arg = %d thread id = %lu\n", *(int*)arg, pthread_self());
  free(arg);
}


void thread_local() 
{
  int* q = pthread_getspecific(key);
  printf("q == %d thread id = %lu\n", *q, pthread_self());
}


void* func1(void* arg)
{
  printf("In func1\n");
  int* s = malloc(sizeof(int));
  *s = 100;
  pthread_setspecific(key, s);
  thread_local();
  printf("Out func1\n");
  return NULL;
}

void* func2(void* arg)
{
  printf("In func2\n");
  int* s = malloc(sizeof(int));
  *s = -100;
  pthread_setspecific(key, s);
  thread_local();
  printf("Out func2\n");
  return NULL;
}

int main() {
  pthread_key_create(&key, key_destructor1);
  pthread_t t1, t2;
  pthread_create(&t1, NULL, func1, NULL);
  pthread_create(&t2, NULL, func2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_key_delete(key);
  return 0;
}
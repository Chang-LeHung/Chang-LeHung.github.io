

#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

void* task(void* arg) {

  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  while(1) {
    
  }
  return NULL;
}

int main() {
  printf("parent id = %d\n", getpid());
  void* res;
  pthread_t t;
  pthread_create(&t, NULL, task, NULL);
  int s = pthread_cancel(t);
  if(s != 0)
    fprintf(stderr, "cancel failed\n");
  pthread_join(t, &res);
  assert(res == PTHREAD_CANCELED);
  return 0;
}
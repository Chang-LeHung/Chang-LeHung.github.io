

#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>



void* task(void* arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
  sleep(1);
  int a = 1;
  while(1) {
    
  }
  return NULL;
}

int main() {

  void* res;
  pthread_t t1;
  pthread_create(&t1, NULL, task, NULL);
  printf("Hello World\n");
  int s = pthread_cancel(t1);
  if(s != 0) // s == 0 mean call successfully
    fprintf(stderr, "cancel failed\n");
  pthread_join(t1, &res);
  assert(res == PTHREAD_CANCELED);
  return 0;
}



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

  void* res;
  pthread_t t1;
  pthread_create(&t1, NULL, task, NULL);
  sleep(1);
  int s = pthread_cancel(t1);
  if(s != 0)
    fprintf(stderr, "cancel failed\n");
  pthread_join(t1, &res);
  assert(res == PTHREAD_CANCELED);
  return 0;
}
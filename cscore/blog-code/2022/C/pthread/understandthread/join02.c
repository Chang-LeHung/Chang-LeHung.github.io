

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

pthread_t t1, t2;

void* thread_1(void* arg) {

  sleep(2);
  return NULL;
}

void* thread_2(void* arg) {

  pthread_join(t1, NULL);
  return NULL;
}

int main() {

  pthread_create(&t1, NULL, thread_1, NULL);
  pthread_create(&t2, NULL, thread_2, NULL);
  sleep(1);
  int ret = pthread_join(t1, NULL);
  if(ret == ESRCH)
    printf("No thread with the ID thread could be found.\n");
  else if(ret == EINVAL) {
    printf("thread is not a joinable thread or Another thread is already waiting to join with this thread\n");
  }
  pthread_join(t2, NULL);
  return 0;
}

#include <errno.h>
#include <linux/futex.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>


int futex_op = 1;

void* mwait(void* args) {
  sleep(5);
  printf("tid = %ld : ready to sleep\n", (long int)pthread_self());
  int *rc = (int*)malloc(sizeof(int));
  struct timespec timeout = {.tv_sec = 0, .tv_nsec = 500000000};
  *rc = (int)syscall(SYS_futex, &futex_op, FUTEX_WAIT, 1, &timeout, NULL, 0);
  printf("tid = %ld : rc = %d\n", (long int)pthread_self(), *rc);
  return rc;
}

void* mwake(void* args) {
  printf("tid = %ld : ready for waking up\n", (long int)pthread_self());
  sleep(2);
  int *rc = (int*)malloc(sizeof(int));
  *rc = syscall(SYS_futex, &futex_op, FUTEX_WAKE, 1, NULL, NULL, 0);
  printf("tid = %ld : rc = %d\n", (long int )pthread_self(), *rc);
  return rc;
}

int main() {
  printf("start to wait sizeof(long int ) = %ld\n", sizeof(long int ));
  
  pthread_t w1, w2;
  pthread_create(&w1, NULL, mwait, NULL);
  pthread_create(&w2, NULL, mwake, NULL);
  void **ret;
  pthread_join(w1, NULL);
  pthread_join(w2, ret);
  printf("ret = %d\n", **(int**)ret);
  return 0;
}
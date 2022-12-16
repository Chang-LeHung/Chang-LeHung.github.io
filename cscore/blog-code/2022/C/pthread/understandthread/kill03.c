
#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sig(int signo) {
  char s[1024];
  sprintf(s, "signo = %d tid = %d pthread tid = %ld\n", signo, gettid(), pthread_self());
  write(STDOUT_FILENO, s, strlen(s));
}

void sig2(int signo) {
  char* s = "thread-defined\n";
  write(STDOUT_FILENO, s, strlen(s));
}

void* func(void* arg) {
  signal(SIGSEGV, sig2);
  printf("pthread tid = %ld\n", pthread_self());
  for(;;);
  return NULL;
}

void* func02(void* arg) {
  printf("pthread tid = %ld\n", pthread_self());
  for(;;);
  return NULL;
}

int main() {
  signal(SIGSEGV, sig);
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  sleep(1);
  pthread_t t2;
  pthread_create(&t2, NULL, func02, NULL);
  sleep(1);
  pthread_kill(t2, SIGSEGV);
  sleep(2);
  return 0;
}
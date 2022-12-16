
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

void* func(void* arg) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGTERM);
  pthread_sigmask(SIG_BLOCK, &set, NULL);
  printf("func : pthread tid = %ld\n", pthread_self());
  for(;;);
  return NULL;
}

void* func02(void* arg) {
  printf("func02 : pthread tid = %ld\n", pthread_self());
  for(;;);
  return NULL;
}

int main() {
  signal(SIGTERM, sig);
  pthread_t t1;
  pthread_create(&t1, NULL, func, NULL);
  sleep(1);
  pthread_t t2;
  pthread_create(&t2, NULL, func02, NULL);
  sleep(1);
  pthread_kill(t1, SIGTERM);
  pthread_kill(t2, SIGTERM);
  sleep(2);
  return 0;
}
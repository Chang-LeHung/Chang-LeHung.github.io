
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
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGTERM);
  pthread_sigmask(SIG_BLOCK, &set, NULL);
  printf("pthread tid = %ld\n", pthread_self());
  for(;;);
  return NULL;
}

int main() {
  signal(SIGHUP, sig);
  signal(SIGTERM, sig);
  signal(SIGSEGV, sig);
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);

  sleep(1);
  pthread_kill(t, SIGHUP);
  sleep(1);
  printf("================\n");
  sleep(1);
  pthread_kill(t, SIGTERM);
  pthread_kill(t, SIGSEGV);
  sleep(1);
  return 0;
}
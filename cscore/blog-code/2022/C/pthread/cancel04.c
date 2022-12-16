
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void sig(int sig) {
  char s[1024];
  sprintf(s, "signo = %d\n", sig);
  write(STDOUT_FILENO, s, strlen(s));
  _exit(1);
}

int main() {
  signal(SIGRTMIN + 1, sig);
  printf("pid = %d\n", getpid());
  sleep(2);
  kill(getpid(), SIGRTMIN + 1);
  return 0;
}
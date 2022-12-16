
#define _GNU_SOURCE
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void my_handler (int signo, siginfo_t *si, void*ucontext)
{
  char s[1024];
  sprintf(s, "发送信号的进程号 = %d 信号 = %d\n", si->si_pid, signo);
  write(STDOUT_FILENO, s, strlen(s));
  _exit(0);
}

int main()
{
  printf("pid = %d\n", getpid());
  struct sigaction demo;
  demo.sa_sigaction = my_handler;
  demo.sa_flags |= SA_SIGINFO;
  sigaction(SIGINT, &demo, NULL);
  sigaction(SIGQUIT, &demo, NULL);
  sigaction(SIGTSTP, &demo, NULL);
  while(1);
  return 0;
}

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
#include <assert.h>

void my_handler (int signo, siginfo_t *si, void*ucontext)
{
  char s[1024];
  int fd = open("text.txt", O_APPEND | O_RDWR | O_CREAT, 0644);
  if(fd == -1)
  {
    perror("");
    abort();
  }
  sprintf(s, "发送信号的进程号 = %d 信号 = %d\n", si->si_pid, signo);
  write(fd, s, strlen(s));
  close(fd);
  fsync(fd);
  _exit(0);
}

int main()
{
  printf("pid = %d\n", getpid());
  struct sigaction demo;
  demo.sa_sigaction = my_handler;
  demo.sa_flags |= SA_SIGINFO;
  demo.sa_flags &= ~SA_RESETHAND;
  sigaction(SIGINT, &demo, NULL);
  sigaction(SIGQUIT, &demo, NULL);
  sigaction(SIGTSTP, &demo, NULL);
  sigaction(SIGHUP, &demo, NULL);
  while(1);
  return 0;
}
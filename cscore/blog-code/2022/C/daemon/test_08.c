
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
#include <sys/types.h>
#include <sys/wait.h>

void my_handler (int signo, siginfo_t *si, void*ucontext)
{
  char s[1024];
  sprintf(s, "pid = %d ppid = %d si->si_pid = %d\n", getpid(), getppid(), si->si_pid);
  write(STDOUT_FILENO, s, strlen(s));
  fsync(STDOUT_FILENO);
  _exit(0);
}

int main()
{
  printf("pid = %d ppid = %d\n", getpid(), getppid());
  sleep(1);
  struct sigaction demo;
  demo.sa_handler = my_handler;
  demo.sa_flags |= SA_SIGINFO;
  sigaction(SIGTSTP, &demo, NULL);
  if(fork())
  {
    wait(NULL);
  }
  else
  {
    printf("pid = %d ppid = %d\n", getpid(), getppid());
    while(1)
    {
      sleep(1);
    }
  }
  return 0;
}
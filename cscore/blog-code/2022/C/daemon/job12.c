
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


void sig(int no, siginfo_t* si, void* ucontext)
{
  char s[1024];
  sprintf(s, "signal number = %d sending pid = %d\n", no, si->si_pid);
  write(STDOUT_FILENO, s, strlen(s));
  sync();
  _exit(0);
}

int main()
{
  struct sigaction action;
  action.sa_flags |= SA_SIGINFO;
  action.sa_sigaction = sig;
  action.sa_flags &= ~(SA_RESETHAND);
  sigaction(SIGTTOU, &action, NULL);
  while(1)
  {
    sleep(1);
    printf("c");
    fflush(stdout);
  }
  return 0;
}
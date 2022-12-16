
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
}

int main()
{
  struct sigaction action;
  action.sa_flags |= SA_SIGINFO;
  action.sa_sigaction = sig;
  action.sa_flags &= ~(SA_RESETHAND);
  sigaction(SIGCONT, &action, NULL);
  while(1)
  {
    sleep(1);
    if(getpgid(0) == tcgetpgrp(STDOUT_FILENO))
    {
      printf("I am a process of foregroup process\n");
    }
  }
  return 0;
}
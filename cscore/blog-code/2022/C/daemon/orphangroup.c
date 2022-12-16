
#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

void sig(int no, siginfo_t *info, void* context)
{
  char s[1024];
  int fd = open("text.txt", O_RDWR | O_CREAT, 0644);
  sprintf(s, "No = %d pid = %d\n", no , info->si_pid);
  write(fd, s, strlen(s));
  close(fd);
  sync();
}

int main()
{
  struct sigaction action;
  action.sa_sigaction = sig;
  action.sa_flags |= SA_SIGINFO;
  action.sa_flags |= ~(SA_RESETHAND);
  sigaction(SIGHUP, &action, NULL);
  pid_t pid = fork();
  if(pid == -1)
  {
    perror("fork:");
  }
  if(pid != 0)
  {
    kill(pid, SIGSTOP);
  }
  else
  {
    while(1);
  }
  return 0;
}
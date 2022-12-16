
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
#include <sys/ioctl.h>

void my_handler (int signo, siginfo_t *si, void*ucontext)
{
  char s[1024];
  // ppid 和 si->si_pid 的进程号相等
  // si->si_pid 就是给这个进程发送信号的进程号
  sprintf(s, "pid = %d ppid = %d si->si_pid = %d signo = %d\n",
       getpid(), getppid(), si->si_pid, signo);
  int fd = open(s, O_RDWR | O_CREAT, 0644);
  write(fd, s, strlen(s));
  fsync(fd);
  _exit(0);
}

int main()  
{
  struct sigaction demo;
  demo.sa_handler = my_handler;
  demo.sa_flags |= SA_SIGINFO;
  sigaction(SIGHUP, &demo, NULL);
  sigaction(SIGCONT, &demo, NULL);
  sigaction(SIGINT, &demo, NULL);
  pid_t pid = fork();
  if(pid == 0)
  {
    int fd = open("/dev/tty", O_RDWR);
    ioctl(fd, TIOCNOTTY, NULL);
  }
  while(1);
  return 0;
}
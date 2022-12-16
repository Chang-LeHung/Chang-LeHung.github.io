
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
  
  printf("pid = %d ppid = %d sid = %d\n", getpid(), getppid(), getsid(0));
  sleep(10);
  return 0;
}
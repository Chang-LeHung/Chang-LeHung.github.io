

#include <stdio.h>
#include <unistd.h>
#include <err.h>

int main()
{
  pid_t pid = fork();
  if(pid == -1)
  {
    perror("fork:");
  }
  printf("pid = %d ppid = %d\n", getpid(), getppid());
  sleep(1);
  if(pid == 0)
  {
    do
    {
      sleep(1);
      printf("pid = %d ppid = %d\n", getpid(), getppid());
    } while (1);
    
  }

  return 0;
}
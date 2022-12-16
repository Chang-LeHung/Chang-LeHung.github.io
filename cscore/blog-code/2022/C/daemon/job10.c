
#include <stdio.h>
#include <unistd.h>
#include <err.h>

int main()
{
  int ret = fork();
  if(ret == -1)
    perror("fork failed:");
  printf("pid = %d\n", getpid());
  while(1)
  {
    printf("pid = %d c = %c\n", getpid(), getchar());
  }
  return 0;
}
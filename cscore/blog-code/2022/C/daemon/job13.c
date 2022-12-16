
#include <stdio.h>
#include <unistd.h>

int main()
{
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
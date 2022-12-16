
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig(int no)
{
  printf("no = %d\n", no);
}

int main()
{
  signal(SIGCONT, sig);
  while(1)
  {
    sleep(1);
    printf("Hello World\n");
  }
  return 0;
}
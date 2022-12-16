
#include <stdio.h>
#include <signal.h>

void sig(int no)
{
  printf("Hello World\n");
}

int main()
{
  signal(SIGSEGV, sig);
  int* i = ((void*)(0));
  int j = *i;
  return 0;
}
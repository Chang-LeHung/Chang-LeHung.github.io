
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sig(int signo)
{
  char* s = "received a signal\n";
  write(STDOUT_FILENO, s, strlen(s));
}

int main()
{
  signal(SIGINT, sig);
  while(1);
  return 0;
}

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sig(int no)
{
  char* s = "Hello World\n";
  write(STDOUT_FILENO, s, strlen(s));
  sync();
}

int main(int argc, char* argv[], char* argvp[])
{

  signal(SIGINT, sig);
  execvp(argv[1], argv);
}


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

void sig(int no) {

  char* s = "recevied sigchild signal\n";
  write(STDOUT_FILENO, s, strlen(s));
}

int main() {

  signal(SIGCHLD, sig);
  signal(SIGSTOP, SIG_IGN);
  if (fork())
  {
    wait(NULL); // wait for child process die
    printf("paraent process recvied sigchild signal\n");
  }else {
    printf("child process is ready to die\n");
    sleep(100);
  }
  
  return 0;
}
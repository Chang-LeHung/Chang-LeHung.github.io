

#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>

void sig(int s) {

  printf("s = %d\n", s);
}

int main() {
  printf("pid = %d\n", getpid());
  siginfo_t de;
  // signal(15, sig);
  sleep(200);
  return 0;
}
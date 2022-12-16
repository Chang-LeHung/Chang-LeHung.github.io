

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {

  setpriority(PRIO_PROCESS, getpid(), -1);
  if(fork()) {
    printf("child process = %d\n", getpriority(PRIO_PROCESS, getpid()));
  }else{
    printf("parent process = %d\n", getpriority(PRIO_PROCESS, gettid()));
  }

  return 0;
}



#include <stdio.h>
#include <unistd.h>

int main() {
  printf("pid = %d ppid = %d\n", getpid(), getppid());
  int pid = getpid();
  sleep(1);
  for(int i = 0; i < 3; i++) {
    if(!fork())
      break;
      
  }
  if(pid != getpid())
    printf("pid = %d ppid = %d\n", getpid(), getppid());
  sleep(1000000);
  return 0;
}
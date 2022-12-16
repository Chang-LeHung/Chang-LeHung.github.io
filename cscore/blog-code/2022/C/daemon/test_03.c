

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

#define SIZE 20

int main()
{
  if(fork())
    exit(1);
  FILE* fp = fopen("test.txt", "w");
  while(1)
  {
    fprintf(fp, "%lu\n", time(NULL));
    printf("ppid = %d\n", getppid());
    printf("errno = %d\n", errno);
    fflush(fp);
    rewind(fp);
    sleep(1);
  }
  return 0;
}
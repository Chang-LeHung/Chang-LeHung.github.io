

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

int main()
{
  if(fork())
    exit(0);
  FILE* fp = fopen("test.txt", "w");
  while(1)
  {
    fprintf(fp, "%lu\n", time(NULL));
    printf("%lu\n", time(NULL));
    fflush(fp);
    rewind(fp);
    sleep(1);
  }
  return 0;
}
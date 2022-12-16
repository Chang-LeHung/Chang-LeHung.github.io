

#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void sig(int no)
{
  int fd = open("./test1.txt", O_RDWR | O_CREAT, 0644);
  char *s = "Hello World\n";
  write(fd, s, strlen(s));
  fsync(fd);
  _exit(0);
}

int main()
{
  signal(SIGHUP, sig);
  int fd = open("./test2.txt", O_WRONLY | O_CREAT, 0644);
  char s[1024];
  while(1)
  {
    sprintf(s, "time = %lu\n", time(NULL));
    write(fd, s, strlen(s));
    int res = write(STDOUT_FILENO, s, strlen(s));
    if(res == -1)
    {
      sprintf(s, "ERROR = %d\n", errno);
      write(fd, s, strlen(s));
      if(errno == EIO)
      {
        sprintf(s, "ERROR = EIO\n");
        write(fd, s, strlen(s));
      }
    }
    sleep(1);
  }
  return 0;
}
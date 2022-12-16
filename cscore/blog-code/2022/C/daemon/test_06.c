

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <string.h> 

int main()
{
  int fd = open("tt.txt", O_RDWR | O_CREAT, 0644);
  int i = 1;
  while(1)
  {
    char s[1024];
    sprintf(s, "ERROR = %d\n", errno);
    int id = write(fd, s, strlen(s));
    fsync(fd);
    if(id != 0)
      printf("Error = %d i = %d\n", errno, i++);
    sleep(1);
  }
  return 0;
}
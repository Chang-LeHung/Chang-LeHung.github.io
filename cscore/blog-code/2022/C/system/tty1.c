
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <assert.h>
#include <err.h>

int main()
{
  printf("pid = %d pgid = %d\n", getpid(), getpgrp());
  pid_t pid = getpid();
  fork();
  fork();
  if(pid + 2 == getpid())
  {
    // int fd = open("/dev/tty", O_RDWR);
    // ioctl(fd, TIOCNOTTY, NULL);
    close(STDERR_FILENO);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    int fd = open("/dev/tty", O_RDWR);
    if(fd == -1)
    {
      perror("error:");
      printf("errno = %d\n", errno);
      assert(errno == ENXIO);
    }
    // setpgid(getpid(), 0);
    printf("pid = %d pgid = %d\n", getpid(), getpgrp());
  }
  while(1);
  return 0;
}
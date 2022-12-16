
#include <stdio.h>
#include <unistd.h>

int main()
{
  // 打印进程的 id 号
  printf("process id = %d\n", getpid());
  // 打印进程的进程组号 0 表示返回当前进程的进程组号
  printf("process group id = %d\n", getpgid(0));
  // 打印进程的父进程号
  printf("parent process id = %d\n", getppid());
  // 打印父进程的进程组号
  printf("parent process group id = %d\n", getpgid(getppid()));
  return 0;
}
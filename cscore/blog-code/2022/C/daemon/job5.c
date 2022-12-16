
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sig(int signo) // signo 这个参数就是对应信号的数字表示 SIGINT 信号对应的数字为 2
{
  char s[1024];
  sprintf(s, "received a signal %d\n", getpid());
  write(STDOUT_FILENO, s, strlen(s));
}

int main()
{
  // 注册收到 SIGINT 信号的时候，我们应该使用什么处理函数
  // 当进程收到 SIGINT 信号的时候，会调用函数 sig 
  signal(SIGINT, sig);
  fork();
  fork();
  while(1);
  return 0;
}
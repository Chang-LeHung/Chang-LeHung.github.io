
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg)
{
  // 默认是 enable  线程的取消机制是开启的
  // 设置取消机制为异步取消
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  while(1);
  return NULL;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  pthread_cancel(t);
  void* res;
  pthread_join(t, &res);
  if(res == PTHREAD_CANCELED)
  {
    printf("thread was canceled\n");
  }
  return 0;
}
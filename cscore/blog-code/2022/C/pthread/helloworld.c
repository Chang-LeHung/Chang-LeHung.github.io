

#include <stdio.h>
#include <pthread.h>

void* func(void* arg) {
  printf("Hello World from tid = %ld\n", pthread_self()); // pthread_self 返回当前调用这个函数的线程的线程 id
  return NULL;
}

int main() {

  pthread_t t; // 定义一个线程
  pthread_create(&t, NULL, func, NULL); // 创建线程并且执行函数 func 

  // wait unit thread t finished
  pthread_join(t, NULL);

  printf("thread t has finished\n");
  return 0;
}
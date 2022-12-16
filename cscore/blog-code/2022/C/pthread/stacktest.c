

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int times = 1;

void* func(void* arg) {
  printf("times = %d\n", times);
  times++;
  char s[1 << 20]; // 申请 1MB 内存空间（分配在栈空间上）
  func(NULL);
  return NULL;
}

int main() {

  pthread_t t;
  pthread_create(&t, NULL, func, NULL);
  pthread_join(t, NULL);
  return 0;
}
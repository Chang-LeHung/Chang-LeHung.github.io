

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* func(void* args) {
  while (1)
  {
    /* code */
  }
  
}
int main() {
  for(int i = 0; i < 10; i++) {
    pthread_t tid;
    pthread_create(&tid, NULL, func, NULL);
  }
  while (1)
  {
    sleep(1);
  }
  
  return 0;
}
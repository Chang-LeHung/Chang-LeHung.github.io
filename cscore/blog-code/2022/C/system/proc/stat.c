
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

int main() {
  pthread_t t;
  int s = pthread_cancel(t);
  if(s == ESRCH)
    printf("No thread with the ID thread could be found.\n");
  return 0;
}
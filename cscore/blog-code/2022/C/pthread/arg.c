

#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


typedef struct info {
  char s[1024];
  int  size;
}info_t;

static
void* func(void* arg) {
  info_t* in = (info_t*)arg;
  in->s[in->size] = '\0';
  printf("string in arg = %s\n", in->s);
  return NULL;
}

int main() {

  info_t* in = malloc(sizeof(info_t));
  in->s[0] = 'H';
  in->s[1] = 'e';
  in->s[2] = 'l';
  in->s[3] = 'l';
  in->s[4] = 'o';
  in->s[5] = 'W';
  in->s[6] = 'o';
  in->s[7] = 'r';
  in->s[8] = 'l';
  in->s[9] = 'd';
  in->size = 10;
  pthread_t t;
  pthread_create(&t, NULL, func, (void*)in);
  pthread_join(t, NULL);
  free(in);
  return 0;
}
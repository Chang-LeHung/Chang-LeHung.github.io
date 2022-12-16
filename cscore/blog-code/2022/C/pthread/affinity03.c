

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

pthread_t ids[10];
static int count;
struct sched_param param;

void* func() {
  cpu_set_t cpuset;
  pthread_t thread;
  thread = pthread_self();
  pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
  for (int j = 0; j < CPU_SETSIZE; j++)
    if (CPU_ISSET(j, &cpuset))
        printf("%ld    CPU %d\n", thread, j);
  sleep(1);
  ids[count++] = thread;
  printf("thread = %ld and pid = %d pid = %d\n", thread, gettid(), getpid());
  int a = 1;
  pthread_setschedparam(ids[0], SCHED_FIFO, &param);
  while(1);
  return 0;
}

int main() {
  pthread_attr_t attr1, attr2;
  pthread_attr_init(&attr1);
  pthread_attr_init(&attr2);
  cpu_set_t cpuset;

  /* Set affinity mask to include CPUs 0 to 7 */

  CPU_ZERO(&cpuset);
  CPU_SET(0, &cpuset);
  pthread_t threads[10];
  param.sched_priority = 10;
  pthread_attr_setaffinity_np(&attr1, sizeof(cpu_set_t), &cpuset);
  pthread_attr_setaffinity_np(&attr2, sizeof(cpu_set_t), &cpuset);
  pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
  pthread_attr_setschedparam(&attr1, &param);
  pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
  for(int i = 0; i < 10; i++) {
    pthread_create(threads + i, &attr2, func, NULL);
  }
  for(int i = 0; i < 10; i++) {
    pthread_join(threads[i], NULL);
  }
  for(int i = 0; i < 10; i++) {
    printf("thread[%d] = %ld\n", i, ids[i]);
  }
  pthread_attr_destroy(&attr1);
  pthread_attr_destroy(&attr2);
  return 0;
}
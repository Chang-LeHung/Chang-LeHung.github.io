
#include <stdio.h>
#include <ucontext.h>
#include "coroutine.h"
#include <stdlib.h>
#include <sys/types.h>
#include <vector>

static
void sechdule()
{
  while(schedule_center.n_task != 0)
  {
    schedule_center.sche();
  }
}

static
int coroutine_create(coroutine_t* ct, coroutine_attr_t* co_attr_t, 
            routine func, void* arg) {
  
  __coroutine_t* routine = (__coroutine_t*)malloc(sizeof(__coroutine_t));
  *ct = (u_int64_t)routine;

  routine->cid = *ct;
  routine->arg = arg;
  routine->func = func;
  routine->enter = start_coroutine;
  routine->state = NEW;
  routine->size = __STACK_SIZE;
  getcontext(&routine->context);
  routine->context.uc_stack.ss_sp = routine->stack;
  routine->context.uc_stack.ss_size = routine->size;
  routine->context.uc_link = &schedule_center.main;
  makecontext(&routine->context, routine->enter, 0);
  coroutine_add(&schedule_center, routine);
  return 0;
}

static
int coroutine_join(coroutine_t ct, void** ret)
{
  __coroutine_t* routine = (__coroutine_t*)ct;

  routine->next = schedule_center.head;
  routine->prev = schedule_center.tail;
  schedule_center.head->prev = routine;
  schedule_center.tail->next = routine;

  while(routine->state != TERMINATED)
  {
    routine = schedule_center.head;
    routine->caller_context = &schedule_center.curr->context;
    swapcontext(&schedule_center.main, &routine->context);

    routine->next->prev = routine->prev;
    routine->prev->next = routine->next;

    schedule_center.head = routine->next;
    coroutine_add(&schedule_center, routine);
  }
  ret = (void**) &(routine->ret);
  coroutine_remove(&schedule_center, ct);
  return 0;
}

static
void coroutine_yield()
{
  __coroutine_t* routine = schedule_center.curr;
  routine->state = READY;
  swapcontext(&routine->context, routine->caller_context);
}

static
coroutine_t coroutine_self()
{
  return schedule_center.curr->cid;
}

void* func(void* arg)
{
  int i, j;
  for(i = 1; i < 10; ++i) 
  {
    for(j = 1; j <= i; ++j) {
      printf("%d x %d = %d\t", i, j, i * j);
    }
    printf("\n");
  }
  printf("yield\n");
  coroutine_yield();
  printf("resumed\n");
  return NULL;
}


int main() {
  
  coroutine_t cid1, cid2;

  coroutine_create(&cid1, NULL, func, NULL);
  coroutine_create(&cid2, NULL, func, NULL);

  coroutine_join(cid1, NULL);
  coroutine_join(cid2, NULL);
  return 0;
}



#ifndef __COROUTINE
#define __COROUTINE

#define __STACK_SIZE 1 << 20
#include <ucontext.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>

typedef long int coroutine_t;
typedef void* (*routine)(void*);
typedef void (*sechedule)(void);
typedef void (*__func) (void);

enum coroutine_state
{
  NEW,
  RUNNING,
  READY,
  TERMINATED
};

typedef struct __coroutine{
  // state of this coroutine
  enum coroutine_state state;
  // ucontext function
  __func enter;
  // user function to be executed
  routine func;
  // arg of func
  void* arg;
  // context of this coroutine
  ucontext_t context;
  // coroutine id
  coroutine_t cid;
  // execution stack
  char stack[__STACK_SIZE];
  int size;
  // return value of func
  void* ret;
  // caller context
  ucontext_t* caller_context;
  // next coroutine
  struct __coroutine* next;
  // previous coroutine
  struct __coroutine* prev;
}__coroutine_t;


typedef struct sche
{
  std::vector<__coroutine_t *> tasks(10);
  __coroutine* curr; // current running routine
  sechedule sche;
  ucontext_t  main;
  long int n_task; // number task
}sche_t;


// global sechduler
sche_t schedule_center;


typedef struct {

}coroutine_attr_t;

static inline void coroutine_add(sche_t* s, __coroutine_t* ct)
{
  if(ct->caller_context == NULL)
  {
    ct->caller_context = &(s->main);
  }
  if(s->head == NULL)
  {
    s->head = s->tail = ct;
    ct->next = ct;
    ct->prev = ct;
    return;
  }

  assert(s->head != NULL && s->tail != NULL);
  s->tail->next = ct;
  ct->prev = s->tail;
  s->tail = ct;
  ct->next = s->head;
  s->head->prev = ct;
}

static inline void coroutine_remove(sche_t* s, coroutine_t coroutine)
{
  __coroutine_t* ct = (__coroutine_t*) coroutine;
  ct->prev->next = ct->next;
  ct->next->prev = ct->prev;
  free(ct);
  s->n_task--;
}


// 启动协中的函数执行 并且获取返回值
void start_coroutine()
{
  __coroutine_t* ct = schedule_center.curr;
  ct->state = RUNNING;
  ct->ret = ct->func(ct->arg);
  ct->state = TERMINATED;
}

#endif // !__COROUTINE

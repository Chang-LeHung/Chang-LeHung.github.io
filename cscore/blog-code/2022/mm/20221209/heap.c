
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

#define type int

typedef int (*_comp)(const type*, const type*);

typedef struct heap{
  size_t capacity;
  type* data;
  size_t size;
  _comp compare;
}heap_t;

void heapify(heap_t* heap);

void heap_down(heap_t* heap, int idx);

void heap_down(heap_t* heap, int idx)
{
  while(idx <= heap->size / 2)
  {
    int L = (idx << 1) + 1;
    int R = (idx + 1) << 1;
    if(L >= heap->size)
      break;

    if(R < heap->size)
    {
      if(heap->compare(&heap->data[idx], &heap->data[L]) && 
         heap->compare(&heap->data[idx], &heap->data[R]))
        break;
      int ex = L;
      if(!heap->compare(&heap->data[L], &heap->data[R]))
        ex = R;
      type tmp = heap->data[ex];
      heap->data[ex] = heap->data[idx];
      heap->data[idx] = tmp;
      idx = ex;
    }
    else
    {
      if(!heap->compare(&heap->data[idx], &heap->data[L]))
      {
        type tmp = heap->data[L];
        heap->data[L] = heap->data[idx];
        heap->data[idx] = tmp;
      }
      break;
    }
  }
}

void heapify(heap_t* heap)
{
  for(int i = heap->size / 2; i >=0 ; --i)
  {
    heap_down(heap, i);
  }
}

int cmp(const type* a, const type* b)
{
  return *a < *b;
}


heap_t* heap_t_alloc(size_t size)
{
  heap_t* res = malloc(sizeof(heap_t));
  res->data = malloc(sizeof(type) * size);
  res->capacity = size;
  res->size = 0;
  res->compare = cmp;
  return res;
}

void heap_add(heap_t *heap, const type *data)
{
  if(heap->size >= heap->capacity)
  {
    type* new_area = malloc(sizeof(type) * 2 * heap->capacity);
    assert(new_area != NULL);
    memcpy(new_area, heap->data, heap->size * sizeof(type));
    heap->data = new_area;
  }
  heap->data[heap->size++] = *data;
}

void heap_sort(heap_t *heap)
{
  size_t restore = heap->size;
  for(int i = 0; i < restore; i++)
  {
    type tmp = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heap->data[heap->size] = tmp;
    heap_down(heap, 0);
  }
  heap->size = restore;
}

int main()
{
  int size = 5;
  struct timeval start, end;

  srand(time(NULL));
  type data;
  heap_t* heap = heap_t_alloc(1000);
  for(int i = 0; i < size; ++i)
  {
    data = rand() % 10000;
    heap_add(heap, &data);
  }
  gettimeofday( &start, NULL );
  heapify(heap);
  heap_sort(heap);
  gettimeofday( &end, NULL );
  for(int i = 0; i < heap->size; ++i)
  {
    printf("%d\n", heap->data[i]);
  }
  double timeuse = 1000 * ( end.tv_sec - start.tv_sec ) + (double)(end.tv_usec - start.tv_usec) / 1000; 
  printf("time: %.5lf ms\n", timeuse);
  int use = 1000000 * ( end.tv_sec - start.tv_sec ) + (end.tv_usec - start.tv_usec); 
  printf("time: %dus\n", use);
  return 0;
}
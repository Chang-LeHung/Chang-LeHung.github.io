

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

typedef struct list
{
  char *data; // 存储具体的数据
  size_t size; // 数据当中数据的个数
  size_t capacity; // 链表的容量
}list_t;

int type; // type == 1 十进制  type == 0 二进制
int sign; // 0 positive 1 negative
list_t *t;
char buf[1024];

void list_add(list_t *list, char c)
{
  if(list->size >= list->capacity)
  {
    if(list->capacity == 0) list->capacity = 1;
    list->capacity <<= 1; 
    char* new_area = malloc(list->capacity);
    if(list->size != 0)
      memcpy(new_area, list->data, list->capacity);
    list->data = new_area;
  }
  list->data[list->size++] = c;
  list->data[list->size] = 0;
}

list_t* init()
{
  list_t* list = malloc(sizeof(list_t));
  list->size = list->capacity = 0;
  return list;
}

size_t list_size(list_t* list)
{
  return list->size;
}

char list_get(list_t* list, int idx)
{
  assert(list->size > idx);
  return list->data[idx];
}

void scan()
{
  for(int i = 0; i < list_size(t); ++i)
  {
    char c = list_get(t, i);
    if(!(c == '0' || c == '1' || c == '.'))
    {
      type = 1;
      return;
    }
  }
  type = 0;
}

float binary2decimal()
{
  uint32_t ires = 0;
  float fres = 0;
  float divsor = 1;
  size_t point = 0;
  for(int i = 0; i < list_size(t); ++i)
  {
    char c = list_get(t, i);
    if(c == '.')
    {
      point = i;
      continue;
    }
    if(point != 0)
    {
      if(c == '1')
      {
        divsor /= 2;
        fres += divsor;
      }
    }
    else
    {
      if(c == '1')
      {
        ires <<=1;
        ires |= 1;
      }
      else
      {
        ires <<= 1;
      }
    }
    
  }
  return ires + fres;
}

void decimal2binary()
{
  int rs = 0;
  int i_part = 0;
  float divsor = 1;
  float f_part = 0;
  int pos = 0;
  for(int i = 0; i < list_size(t); ++i)
  {
    char c = list_get(t, i);
    if(c == '.')
    {
      pos = i;
      continue;
    }
    if(pos != 0)
    {
      divsor /= 10;
      f_part += divsor * (c - '0');
      continue;
    }
    i_part *= 10;
    i_part += c - '0';
  }
  char s[64];
  pos = 64;
  while(i_part / 2 > 0)
  {
    s[--pos] = '0' + (i_part & 1);
    i_part /= 2;
  }
  s[--pos] = '0' + (i_part & 1);
  for(int i = pos; i < 64;)
  {
    buf[rs++] = s[i++];
  }
  buf[rs++] = '.';
  for(int i = 0; i < 10; i++)
  {
    f_part *= 2;
    if(f_part > 1)
    {
      buf[rs++] = '1';
      f_part -= 1;
    }
    else
      buf[rs++] = '0';
  }
  buf[rs++] = 0;
}

int main()
{
  t = init();
  char c = getchar();
  if(c == '-')
  {
    sign = 1;
    c = getchar();
  }
  else
  {
    sign = 0;
  }
  while(c != '#')
  {
    list_add(t, c);
    c = getchar();
  }
  scan();
  if(type == 0)
  {
    float res =  binary2decimal();
    if(sign)
      res = -res;
    printf("res = %lf\n", res);
  }
  else
  {
    decimal2binary();
    if(sign)
      printf("-");
    printf("res = %s\n", buf);
  }
  return 0;
}
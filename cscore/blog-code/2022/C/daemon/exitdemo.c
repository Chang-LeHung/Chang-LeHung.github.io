

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void a()
{
  printf("a\n");
}

void b()
{
  printf("b\n");
}

int main()
{
  atexit(b);
  int c = 1;

  on_exit(a, NULL);

  return 0;
}
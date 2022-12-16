

#include <stdio.h>

#define new_line printf("\n");

int main()
{
  for(int i = 0; i < 16; ++i)
  {
    for(int j = 0; j < 16; ++j)
    {
      printf("\033[38;5;%d;48;5;%dm", j * 16 + i, i * 16 + j);
      printf("A ");
    }
    printf("\033[m");
    new_line
  }
  new_line
  return 0;
}

#include <stdio.h>
#include <unistd.h>

#define ansi_start     "\033["

#define Up(n)          ansi_start "%dA", n
#define Down(n)        ansi_start "%dB", n
#define Right(n)       ansi_start "%dC", n
#define Left(n)        ansi_start "%dD", n


#define Black       "40"
#define Red         "41"
#define Green       "42"
#define Yellow      "43"
#define Blue        "44"
#define Magenta     "45"
#define Cyan        "46"
#define White       "47"
#define Reset       "0"

#define no_bright   "m"
#define bright      ";1m"

#define concat(x, y) ansi_start x y

#define print_with_color(x, str) \
        printf(concat(x, no_bright) str concat(Reset, no_bright));


int main()
{

  printf("##########\n");
  for(int i = 0; i < 8; ++i)
  {
    printf("#");
    printf(Right(8));
    printf("#\n");
  }
  printf("##########\n");
  printf("\n");

  printf("##########\n");
  for(int i = 0; i < 8; ++i)
  {
    printf("#");
    print_with_color(Red, "        ")
    printf("#\n");
  }
  printf("##########\n");
  printf("\n");
  return 0;
}


#include <sys/ioctl.h>
#include <stdio.h>

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

#define BackTo00 printf("\033[H");
#define Up(n)          ansi_start "%dA", n
#define Down(n)        ansi_start "%dB", n
#define Right(n)       ansi_start "%dC", n
#define Left(n)        ansi_start "%dD", n

#define MoveTo(x, y)      \
        BackTo00          \
        printf(Right(x));  \
        printf(Down(y));

#define ClearCurrentLine ansi_start "2K"

int main (void)
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    for(int i = 0; i < w.ws_row; ++i)
    {
      for(int j = 0; j < w.ws_col / 2; j++)
      {
        print_with_color(Yellow, " ")
      }
      printf(" ");
      for(int j = w.ws_col / 2 + 1; j < w.ws_col; j++)
      {
        print_with_color(Cyan, " ")
      }
      // printf("\n");
    }
    printf("\n");

    return 0;
}
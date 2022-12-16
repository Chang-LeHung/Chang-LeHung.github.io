

#include <stdio.h>

#define ansi_start  "\033["
#define Black       "30"
#define Red         "31"
#define Green       "32"
#define Yellow      "33"
#define Blue        "34"
#define Magenta     "35"
#define Cyan        "36"
#define White       "37"
#define Reset       "0"

#define no_bright   "m"
#define bright      ";1m"

#define colors      "48;5;"

#define concat(x, y, z) ansi_start x y z

#define print_with_colors(str, ...) \
        printf(concat(colors, str, "") concat(Reset, "", no_bright), __VA_ARGS__);
#define new_line printf("\n");

int main()
{
  for(int i = 0; i < 16; ++i)
  {
    for(int j = 0; j < 16; ++j)
    {
      print_with_colors("%dm %-3d", i * 16 + j, i * 16 + j)
    }
    new_line
  }
  new_line
  return 0;
}
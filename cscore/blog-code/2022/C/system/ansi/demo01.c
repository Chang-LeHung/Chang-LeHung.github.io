

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

#define Bold        "1"
#define Underline   "4"
#define Reversed    "7"

#define concat(x, y) ansi_start x y

#define print_with_color(x, str) \
        printf(concat(x, no_bright) str concat(Reset, no_bright));
#define print_with_color_bright(x, str) \
        printf(concat(x, bright) str concat(Reset, bright));

int main()
{
  print_with_color(Black, "Hello World\t")
  print_with_color(Red, "Hello World\t")
  print_with_color(Black, "Hello World\t")
  print_with_color(Yellow, "Hello World\t")
  printf("\n");
  print_with_color(Blue, "Hello World\t")
  print_with_color(Magenta, "Hello World\t")
  print_with_color(Cyan, "Hello World\t")
  print_with_color(White, "Hello World\t")
  printf("\n");
  printf("==================================\n");
  print_with_color_bright(Black, "Hello World\t")
  print_with_color_bright(Red, "Hello World\t")
  print_with_color_bright(Black, "Hello World\t")
  print_with_color_bright(Yellow, "Hello World\t")
  printf("\n");
  print_with_color_bright(Blue, "Hello World\t")
  print_with_color_bright(Magenta, "Hello World\t")
  print_with_color_bright(Cyan, "Hello World\t")
  print_with_color_bright(White, "Hello World\t")
  printf("\n");

  printf("Decorations\n");

  print_with_color(Bold, "Hello World\t")
  print_with_color(Underline, "Hello World\t")
  print_with_color(Reversed, "Hello World\t")

  printf("\n");
  return 0;
}
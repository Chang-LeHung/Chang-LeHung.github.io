

#include <stdio.h>

#define ansi_start "\033["
#define concat(x) ansi_start x

// color
#define black   "30m"
#define red     "31m"
#define green   "32m"
#define yellow  "33m"
#define blue  "34m"
#define magenta  "35m"

#define normal  "0m"

int main() {


  printf(concat(red) "Hello world\n" concat(normal));
  return 0;
}
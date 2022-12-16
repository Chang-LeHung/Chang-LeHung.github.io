#include <stdio.h>

void foo_char_ptr(int a, char *b) {
  printf("Called int, char*.\n");
}

void foo_int(int a, int b) {
  printf("Called int, int.\n");
}

#define foo(a, b) _Generic((b), char*: foo_char_ptr, int: foo_int)(a, b)

int main() {
  foo(1, 1);
  foo(1, "foo");
}

#include <stdio.h>

void foo(int x);

int main(int argc, char** argv) {
  foo(2);
  foo(4);
  foo(2 + 4);
  foo(2 - 4);
  foo(2 * 4);
  foo(2 / 4);
}


void foo(int x) {
  printf("The function foo was passed the number %d\n", x);
}

#include <stdio.h>

int main() {
  printf("Hello World! try 3");

  int x;
  int y;
  int sum;

  x = 0b00001111;
  y = 0b00000001;

  sum = x + y;

  printf("%d + %d = %d", x, y, sum);  

  return sum;
}
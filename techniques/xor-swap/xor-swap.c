#include <stdio.h>
#include <stdlib.h>

#define xorswap(a, b) ((a)^=(b),(b)^=(a),(a)^=(b))

int main()
{
  int a = 5;
  int b = 13;
  printf("a=%d,b=%d\n", a, b);

  xorswap(a, b);
  printf("a=%d,b=%d\n", a, b);

  return 0;
}

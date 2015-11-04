#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

void print(int *v, int length)
{
  int i;
  for (i=0; i<length; i++)
    printf("%d ", v[i]);
  printf("\n");
}

int comp(const void *a, const void *b)
{
  int *x;
  int *y;

  x = (int *)a;
  y = (int *)b;

  return *x > *y;
}

/* Main program. */
int main(int argc, char **argv)
{
  int v[] = {5, 48, 12, 19, 13, 13, 9, 28};
  int length = 7;
  
  qsort(v, length, sizeof(int), &comp);

  print(v, length);
  
  return EXIT_SUCCESS;
}

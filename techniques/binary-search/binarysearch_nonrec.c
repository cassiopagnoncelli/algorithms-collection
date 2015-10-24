#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

/* Prints the vector. */
void print(int *v, int length)
{
  int i;
  for (i=0; i<length; i++)
    printf("%d ", v[i]);
  printf("\n");
}

/* Gives 1 iff a > b. */
int comp(const void *a, const void *b)
{
  int *x = (int *)a;
  int *y = (int *)b;
  return *x > *y;
}

/* Search v[a..b] for x returning its index if found, -1 otherwise. */
int binarysearch(int *v, int length, int x)
{
  int a = 0;
  int b = length - 1;
  int middle;

  while (a <= b)
  {
    middle = (a+b) / 2;

    if (x == v[middle])
      return middle;
    else if (x < v[middle])
      b = middle - 1;
    else
      a = middle + 1;
  }

  return -1;
}

/* Main program. */
int main(int argc, char **argv)
{
  int v[] = {5, 12, 19, 23, 33, 47, 49};
  int length = 7;
  int idx;
  int i;
  
  for (i=0; i<=50; i++) {
    idx = binarysearch(v, length, i);
    idx != -1 ? printf("v[%d] = %d\n", idx, v[idx]) : printf("%d not found\n", i);
  }
  
  return EXIT_SUCCESS;
}

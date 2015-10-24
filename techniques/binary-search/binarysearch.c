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
int binarysearch(int *v, int x, int a, int b)
{
  int middle;

  if (a > b)
    return -1;

  middle = (a + b) / 2;
  if (v[middle] == x)
    return middle;

  return x < v[middle] ? 
    binarysearch(v, x, a, middle-1) :
    binarysearch(v, x, middle+1, b);
}

/* Main program. */
int main(int argc, char **argv)
{
  int v[] = {5, 48, 12, 19, 13, 13, 9, 28};
  int length = 7;
  int idx;
  int i;

  qsort(v, length, sizeof(int), &comp);
  print(v, length);

  for (i=0; i<50; i++) {
    idx = binarysearch(v, i, 0, length-1);
    idx != -1 ? printf("v[%d] = %d\n", idx, v[idx]) : printf("%d not found\n", i);
  }
  
  return EXIT_SUCCESS;
}

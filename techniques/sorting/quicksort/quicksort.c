#include <stdio.h>
#include <stdlib.h>

/* Print to the stdout the elements of the vector. */
void print(int *v, int size)
{
  int i;
  for (i=0; i<size; i++)
    printf("%d ", v[i]);

  printf("\n");
}

/*
  `partition' returns an index I such that:
  - v[a] <= v[I] for all a < I;
  - v[b] >= v[I] for all b > I.
*/
int partition(int *A, int p, int r)
{
  int x, i, j, tmp;

  x = A[r];
  i = p-1;
  
  for (j=p; j<r; j++)
  {
    if (A[j] <= x) {
      i++;                                               /* Advance marker. */

      tmp = A[i];
      A[i] = A[j];
      A[j] = tmp;
                                                      /* Swap v[i] by v[j]. */
    }
  }

  /*swap(&v[i+1], &v[end]);*/                     /* Swap v[i+1] by v[end]. */
  tmp = A[i+1];
  A[i+1] = A[r];
  A[r] = tmp;

  return i+1;
}

/* Non-randomized quicksort, an O(n log n)-time algorithm for sorting. */
void quicksort(int *v, int p, int r)
{
  if (p < r)
  {
    int q = partition(v, p, r);
    quicksort(v, p, q-1);
    quicksort(v, q+1, r);
  }
}

/* Main program. */
int main(int argc, char **argv)
{
  int *v, length;
  
  /* Allocate memory. */
  length = 7;
  if (!(v = malloc(length * sizeof(int))))
    return 1;

  /* Fill vector. */
  v[0] = 5;
  v[1] = 81;
  v[2] = 33;
  v[3] = 42;
  v[4] = 11;
  v[5] = 9;
  v[6] = 19;

  /* Print unordered version. */
  print(v, length);

  /* Sort `v'. */
  quicksort(v, 0, length-1);

  /* Print sorted version of `v'. */
  print(v, length);

  return EXIT_SUCCESS;
}

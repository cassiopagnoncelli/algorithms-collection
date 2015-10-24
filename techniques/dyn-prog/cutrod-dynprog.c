#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MINF -100

int max(int a, int b)
{
  return a > b ? a : b;
}

int cutrod(int *rod, int n)
{
  int q, i;

  if (n == 0)
    return 0;

  q = MINF;
  for (i=1; i<=n; i++)
    q = max(q, rod[i] + cutrod(rod, n-i));

  return q;
}

int memoized_cutrod_aux(int *rod, int n, int *r)
{
  int q, i;

  if (r[n] >= 0)
    return r[n];

  if (n == 0)
    q = 0;
  else {
    q = MINF;
    for (i=1; i<=n; i++)
      q = max(q, rod[i] + memoized_cutrod_aux(rod, n-i, r));
  }

  r[n] = q;
  return q;
}

int memoized_cutrod(int *rod, int n)
{
  int *r = malloc((n+1) * sizeof(int));
  int i;

  for (i=0; i<=n ;i++)
    r[i] = MINF;

  return memoized_cutrod_aux(rod, n, r);
}

int bottomup_cutrod(int *rod, int n)
{
  int *r;
  int i, j, q;

  r = malloc((n+1) * sizeof(int));

  r[0] = 0;
  for (j=1; j<=n; j++) {
    q = MINF;
    for (i=1; i<=j; i++)
      q = max(q, rod[i] + r[j-i]);
    r[j] = q;
  }

  return r[n];
}

int main(int arc, char **argv)
{
  int rod[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};    /* Ignore rod[0]. */
  int length = sizeof(rod) / sizeof(int) - 1;
  int i;

  for (i=1; i<=length; i++)                              /* Rod[1..length]. */
    printf("r_%d = %d = %d = %d\n",
           i,
           cutrod(rod, i),
           memoized_cutrod(rod, i),
           bottomup_cutrod(rod, i));

  return EXIT_SUCCESS;
}

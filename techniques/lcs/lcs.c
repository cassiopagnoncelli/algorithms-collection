/*
 * The `diff' linux program solves the Longest Common Subsequence problem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NONE        0
#define UP          1
#define LEFT        2
#define UPPERLEFT   3

/* Global vars. */
char *X, *Y;
int xlen, ylen;
int **b, **c;

/* Matrix allocation. */
int **imat_alloc(int lins, int cols)
{
  int **M;
  int i;

  M = (int **) malloc((1 + lins) * sizeof(int *));
  for (i = 0; i <= lins; i++)
    M[i] = (int *) malloc((1 + cols) * sizeof(int));

  return M;
}

/* Fill matrices. */
void lcs_length()
{
  int i, j, m, n;

  m = xlen;
  n = ylen;

  for (i = 1; i <= m; i++)
    c[i][0] = 0;

  for (j = 0; i <= n; i++)
    c[0][j] = 0;

  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++) {
      if (X[i] == Y[i]) {
        c[i][j] = c[i-1][j-1] + 1;
        b[i][j] = UPPERLEFT;
      } else if (c[i-1][j] >= c[i][j-1]) {
        c[i][j] = c[i-1][j];
        b[i][j] = UP;
      } else {
        c[i][j] = c[i][j-1];
        b[i][j] = LEFT;
      }
    }
}

void print_lcs(int i, int j)
{
  if (i == 0 || j == 0)
    return;

  if (b[i][j] == UPPERLEFT) {
    print_lcs(i-1, j-1);
    /*printf("%c[%d] ", X[i], i);*/
    printf("%c", X[i]);
  } else if (b[i][j] == UP) {
    print_lcs(i-1, j);
  } else {
    print_lcs(i, j-1);
  }
}

/* Main program. */
int main()
{
  /* Sequences. */
  X = malloc(BUFSIZ * sizeof(char));
  Y = malloc(BUFSIZ * sizeof(char));
  X = " ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
  Y = " GTCGTTCGGAATGCCGTTGCTCTGTAAA";
  xlen = strlen(X);
  ylen = strlen(Y);

  /* Fill matrices `b' and `c'. */
  b = imat_alloc(xlen, ylen);
  c = imat_alloc(xlen, ylen);
  lcs_length();

  /* Print result. */
  printf("X: %s\n", X);
  printf("Y: %s\n", Y);
  printf("LCS: "); print_lcs(xlen, ylen); putchar('\n');

  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

#define termial(n) ( ((n)*((n)+1)) / 2 )

int d, **A, *v;

int max(int a, int b)
{
  return a > b ? a : b;
}

void printmatrix()
{
  int i, j;
  for (i=0; i<d; i++) {
    for (j=0; j<d; j++)
      printf("%3d  ", A[i][j]);
    printf("\n");
  }
}

void printvector()
{
  printf("| ");
  
  int i;
  for (i = 0; i < d*d; i++)
    printf("%d ", v[i]);
 
  printf("\n");
}

void fillall()
{
  int i;
  
  /* Fill A. */
  d = 7;
  A = (int **) malloc(((size_t)d*2) * sizeof(int *));
  for (i=0; i<2*d; i++)
    A[i] = (int *) malloc(((size_t)d*2) * sizeof(int));
  
  /* Fill v. */
  v = (int *) calloc((size_t)(d), sizeof(int));
  
  srand(123);
  for (i = 0; i < d*d; i++)
    v[i] = v[i-1] + 1 + rand() % 5;
}

void dovetailing()
{
  int row, col;
  
  /* Fill 1st row. */
  for (col=0; col<2*d; col++)
    A[0][col] = termial(1+col);
  
  /* First 1st column. */
  for (row=1; row<2*d; row++)
    A[row][0] = A[0][row-1] + 1;
  
  /* Fill other cells. */
  for (row=1; row<2*d; row++)
    for (col=1; row+col<=2*d; col++)
      A[row][col] = A[row][col-1] + ( A[row-1][col+1] - A[row-1][col] );
}

/* principal. */
int
main()
{
  fillall();
  printvector();
  dovetailing();
  printmatrix();
  
  return EXIT_SUCCESS;
}

/*
  Dadas duas palavras, calcular seu edit distance.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edit_distance.h"

/*
  mensagem de erro.
*/
int
erro(const char *str)
{
  fprintf(stderr, "%s.\n", str);
  return EXIT_FAILURE;
}

/*
  imprime matriz
*/
void
imprime_matriz(unsigned int **C, unsigned int linhas, unsigned int colunas)
{
  unsigned int i, j;
  for (i = 0; i < linhas; i++) {
    for (j = 0; j < colunas; j++)
      printf(" %d", C[i][j]);
    printf("\n");
  }
}

/*
  devolve min(a, min(b, c))
*/
unsigned int
minimo(unsigned int a, unsigned int b, unsigned int c)
{
  return (a < b && a < c ? a : (b < c ? b : c));
}

/*
  delta: devolve 1, se os caracteres casam; 0, caso contrário.
*/
unsigned int
delta(const char a, const char b)
{
  return (a == b ? 0 : 1);
}

/*
  edit distance.
*/
unsigned int
edit_distance(const char *p1, const char *p2)
{
  unsigned int i, j,
    m = (unsigned int) strlen(p1),
    n = (unsigned int) strlen(p2),
    **C;

  C = malloc((1 + m) * sizeof(unsigned int *));
  for (i = 0; i <= m; i++)
    C[i] = calloc(1 + n, sizeof(unsigned int));

  for (i = 0; i <= m; i++)
    C[i][0] = i;
  for (i = 0; i <= n; i++)
    C[0][i] = i;

  for (j = 1; j <= n; j++)
    for (i = 1; i <= m; i++)
      C[i][j] = minimo(C[i-1][j] + 1 /* deleção */, 
		       C[i][j-1] + 1 /* inserção */, 
		       C[i-1][j-1] + delta(p1[i-1], p2[j-1]) /* substituição */);

  return C[m][n];
}


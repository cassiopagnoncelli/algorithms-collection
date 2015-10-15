#include <stdio.h>
#include <stdlib.h>

/* mensagem de erro. */
int
erro(const char *str)
{
  fprintf(stderr, "%s.\n", str);
  return EXIT_FAILURE;
}

void
troca(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int
backtracking(int *P, int n, int inicio)
{
  int i;
  if (inicio == n || 1) {
    printf("de %d para %d: ", P[0], P[inicio-1]);
    for (i = 0; i < inicio; i++)
      printf("%d ", P[i]);
      printf("\n");
  }

  for (i = inicio; i < n; i++) {
    troca(&P[i], &P[inicio]);
    if (!backtracking(P, n, inicio + 1)) return 0;
    troca(&P[i], &P[inicio]);
  }

  return 1;
}

/* principal. */
int
main()
{
  int P[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  if (!backtracking(P, 10, 0))
    printf("erro.\n");
  
  return EXIT_SUCCESS;
}

/*
  Bubble sort
  --
  Cássio Jandir Pagnoncelli, kimble9t (em) gmail (ponto) com
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

/* mensagem de erro. */
int
erro(const char *str)
{
  fprintf(stderr, "%s.\n", str);
  return EXIT_FAILURE;
}

void bubble_sort(int *v[], int tam)
{
  int i, trocado, aux, k;
  do {
    trocado = 0;
    for (i=0; i<tam-1; i++)
      if (v[0][i] > v[0][i+1]) {
        aux = v[0][i];
        v[0][i] = v[0][i+1];
        v[0][i+1] = aux;
        trocado = 1;
      }

    for (k=0; k<tam; k++)
      cout << v[0][k] << " ";
    cout << endl;
  } while (trocado == 1);
}

/* principal. */
int
main(int argc, char **argv)
{
  int 
    i,
    n = 10,
    *v = new int[10];

  v[0] = 42;
  v[1] = 60;
  v[2] = 23;
  v[3] = 56;
  v[4] = 13;
  v[5] = 44;
  v[6] = 16;
  v[7] = 29;
  v[8] = 37;
  v[9] = 8;

  bubble_sort(&v, n);

  for (i=0; i<n; i++)
    cout << v[i] << " ";
  cout << endl;
  
  return EXIT_SUCCESS;
}

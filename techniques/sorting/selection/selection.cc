/*
  Selection sort
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

void selection_sort(int *v[], int tam)
{
  int i, j, tmp, k, min;
  for (i=0; i<tam-1; i++) {
    // acha o mínimo
    min = i;
    for (j=i; j<tam; j++)
      if (v[0][j] < v[0][min])
        min = j;

    // troca v[i] com v[j]
    tmp = v[0][i];
    v[0][i] = v[0][min];
    v[0][min] = tmp;
    
    // imprime
    for (k=0; k<i; k++)
      cout << v[0][k] << " ";
    cout << endl;
  }
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

  selection_sort(&v, n);

  for (i=0; i<n; i++)
    cout << v[i] << " ";
  cout << endl;
  
  return EXIT_SUCCESS;
}

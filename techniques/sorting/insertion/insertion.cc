/*
  Insertion sort
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

void insertion_sort(int *v[], int tam)
{
  int i, tmp, j, k;
  for (i=1; i<tam; i++) {
    tmp = v[0][i];
    j = i-1;
    while (j >= 0 && tmp <= v[0][j]) {
      v[0][j+1] = v[0][j];
      j--;
    }

    v[0][j+1] = tmp;

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

  insertion_sort(&v, n);

  for (i=0; i<n; i++)
    cout << v[i] << " ";
  cout << endl;
  
  return EXIT_SUCCESS;
}

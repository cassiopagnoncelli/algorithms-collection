#include <stdio.h>

int main(void) 
{
  int d = 4, v[d * d], m[d][d], start, i, j, k, i0, j0;

  // Fill v with 1,2,...d^2
  for (i = 0; i < d * d; i++) v[i] = i+1;

  // Start dovetail. 
  k = 0;
  for (i0 = 0; i0 < d; i0++)  // Down left column
    for (i = i0, j = 0; i >= 0; i--, j++)
      m[i][j] = v[k++];

  for (j0 = 1; j0 < d; j0++)  // Across bottom row
    for (i = d - 1, j = j0; j < d; i--, j++)
      m[i][j] = v[k++];
  // End dovetail.

  for (i = 0; i < d; i++) {
    for (j = 0; j < d; j++) printf("%4d", m[i][j]);
    printf("\n");
  }
  return 0;
}

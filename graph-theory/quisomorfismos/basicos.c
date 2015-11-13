#include "basicos.h"
#include <stdio.h>

void imprime_matriz(int **M, int l_a, int l_b, int c_a, int c_b) {
	int i, j;
	for ( i=l_a; i<=l_b; i++ ) {
		for ( j=c_a; j<=c_b; j++ )
			printf("%d ", M[i][j]);
		printf("\n");
	}

	printf("\n");
}

int fatorial(int n) {
	int i, acum = 1;
	for ( i=1; i<=n; i++ )
		acum *= i;
	return acum;
}

void troca(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void imprime_permutacao(int *P, int n) {
	printf("<");
	int i;
	for ( i=0; i<n; i++ )
		printf("%d ", P[i]);
	printf("%d>\n", P[n]);
}

int conjuntos_iguais(int *A, int *B, int tam) {
	if ( tam == 0 ) return 1;

	quicksort(A, 1, tam);
	quicksort(B, 1, tam);

	int i;
	for ( i=1; i<=tam; i++ )
		if ( A[i] != B[i] )
			return 0;
	return 1;
}

int particiona(int *V, int inicio, int fim) {
	int i = inicio, j;
	for ( j=inicio+1; j<=fim; ++j ) 
		if ( V[j] < V[inicio] ) {
			i++;
			troca(&V[i], &V[j]);
		}

	troca(&V[inicio], &V[i]);

	return i;
}

void quicksort(int *V, int a, int b) {
	if ( b <= a ) return;

	int meio = particiona(V, a, b);
	quicksort(V, a, meio - 1);
	quicksort(V, meio + 1, b);
}


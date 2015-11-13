#include "grafo.h"
#include <stdlib.h>

grafo *novo(int tam) {
	grafo *G = malloc(sizeof(grafo));
	if ( !G ) return NULL;

	G->num_arestas = 0;
	G->num_vertices = tam;
	
	G->A = malloc((V(G) + 1) * sizeof(int *));
	if ( !G->A ) return NULL;
	int i;
	for ( i=0; i<=V(G); i++ )
		if ( !(G->A[i] = calloc(V(G) + 1, sizeof(int))) ) return NULL;

	return G;
}

grafo *recebe_grafo(FILE * fp) {
	if ( !fp ) return NULL;

	FILE *f = fp;

	// busca dimensoes da matriz de representacao
	int 	lin = 0, 
		col = 0, col_atual = 0;
	char c;
	while ( (c=fgetc(f)) != EOF ) {
		if ( c == '\n' ) {
			lin++;
			col_atual = 0;
		} else {
			col_atual++;
			if ( col_atual > col ) col = col_atual;
		}
	}

	// preenche matriz de representacao
	int **r = malloc(lin * sizeof(int *));
	if ( !r ) return NULL;
	int i, j;
	for ( i=0; i<lin; i++ )
		if ( !(r[i] = calloc(col_atual, sizeof(int))) )
			return NULL;
	rewind(f);
	int k = 0;
	i = 0; j = 0;
	while ( (c=fgetc(fp)) != EOF ) {
		if ( c == 'C' ) r[i][j] = ++k;
		if ( c == '\n' ) {
			i++; j = 0;
		} else 
			j++;
	}

	//imprime_matriz(r, 0, lin-1, 0, col-1);

	grafo *G = novo(k);
	
	// preenche a matriz de adjacencias
	for ( i=0; i<lin; i++ )
		for ( j=0; j<col; j++ )
			if ( r[i][j] > 0 ) {
				// testa para baixo
				if ( i+1 < lin && r[i+1][j] > 0 ) {
					G->A[ r[i][j]   ][ r[i+1][j] ] = 1;
					G->A[ r[i+1][j] ][ r[i][j]   ] = 1;
					E(G)++;
				}
				// testa para direita
				if ( j+1 < col && r[i][j+1] > 0 ) {
					G->A[ r[i][j]   ][ r[i][j+1] ] = 1;
					G->A[ r[i][j+1] ][ r[i][j]   ] = 1;
					E(G)++;
				}
				/*// testa para esquerda
				if ( j-1 >= 0 && r[i][j-1] > 0 ) {
					G->A[ r[i][j]   ][ r[i][j-1] ] = 1;
					G->A[ r[i][j-1] ][ r[i][j]   ] = 1;
				}
				// testa para cima
				if ( i-1 >= 0 && r[i-1][j] > 0 ) {
					G->A[ r[i][j]   ][ r[i-1][j] ] = 1;
					G->A[ r[i-1][j] ][ r[i][j]   ] = 1;
				}*/
			}
	
	// imprime matriz de adjacencias
	//imprime_matriz(G->A, 1, V(G), 1, V(G));

	return G;
}

int *conjunto_graus(grafo *G) {
	int *graus = calloc(V(G) + 1, sizeof(int));
	if ( !graus ) return NULL;

	int i, j;
	for ( i=1; i<=V(G); i++ )
		for ( j=1; j<=V(G); j++ )
			if ( G->A[i][j] > 0 ) 
				graus[i]++;
	
	return graus;
}

int testa_isomorfismo(grafo *G, grafo *H, int *f) {
	//imprime_permutacao(f, V(G));

	int i, j;
	for ( i=1; i<V(G); i++ ) // verificar limites
		for ( j=i+1; j<V(G); j++ ) // verificar limites
			if ( G->A[i][j] != H->A[f[i]][f[j]] ) 
				return 0;
	return 1; // f eh um isomorfismo de G em H
}

int permuta_buscando_isomorfismo(int *P, int inicio, int n, grafo *G, grafo *H) {
	if ( inicio == n - 1 ) 
		return testa_isomorfismo(G, H, P);

	// gera as permutacoes recursivamente em ordem nao-lexicografica
	int i;
	for ( i=inicio; i<=n; i++ ) {
		troca(&P[i], &P[inicio]);
		if ( permuta_buscando_isomorfismo(P, inicio + 1, n, G, H) ) return 1;
		troca(&P[i], &P[inicio]);
	}

	return 0;
}

int existe_bijecao(grafo *G, grafo *H) {
	// verifica dentre as V(G)! funcoes se uma delas eh bijetora
	int 	i, 
		fat = fatorial(V(G)),
		*P = malloc((V(G)+1) * sizeof(int));
	
	// gera estado inicial: <1 2 3 ... n>
	for ( i=1; i<=V(G); i++ )
		P[i] = i;

	// gera grupo de permutacoes buscando isomorfismo de G em H
	return permuta_buscando_isomorfismo(P, 0, V(G), G, H);
}


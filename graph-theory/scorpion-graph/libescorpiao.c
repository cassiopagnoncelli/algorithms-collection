#include "libescorpiao.h"
#include <stdio.h>
#include <stdlib.h>


int grau(grafo *G, int v) {
	int d = 0, i;
	for ( i=1; i<=V(G); i++ )
		if ( G->A[v][i] != 0 ) 
			d++;
	return d;
}

void imprime_grafo(grafo *G) {
	int i, j;
	for ( i=1; i<=V(G); i++ ) {
		for ( j=1; j<=V(G); j++ )
			printf("%d", G->A[i][j]);
		printf("\n");
	}

	printf("\n");
}

grafo *recebe_grafo_adj(FILE *fp) {
	if ( !fp ) return NULL;

	// busca ordem do grafo
	int ordem = 0;
	char c;
	while ( (c=fgetc(fp)) != '\n' )
		ordem++;
	
	// volta o ponteiro de arquivo para o inicio
	rewind(fp);

	// inicia um novo grafo
	grafo *G = malloc(sizeof(grafo));
	if ( !G ) return NULL;

	// aloca matriz de adjacencias
	if ( !(G->A = malloc(sizeof(int) * (ordem + 1))) ) return NULL;
	int i;
	for ( i=1; i<=ordem; i++ )
		if ( !(G->A[i] = calloc(ordem + 1, sizeof(int))) ) 
			return NULL;
	
	// recebe matriz de adjacencias do arquivo
	i = 1;		// representa as linhas do arquivo
	int j = 1;	// representa as colunas do arquivo
	while ( (c=fgetc(fp)) != EOF ) {
		if ( c == '\n' ) {
			j = 1;
			i++;
		} else {
			
			G->A[i][j] = (c == '0' ? 0 : 1);
			j++;
		}
	}

	// V(G) <- ordem da matriz de adjacências
	V(G) = ordem;

	return G;
}

int escorpiao(grafo *G) {
	// busca um vertice b que satisfaça a primeira propriedade
	int i, b = 0;
	for ( i=1; i<=V(G); i++ )
		if ( grau(G, i) == V(G) - 2 )
			b = i;
	
	// não satisfazendo a primeira propriedade sabe-se G não é escorpião
	if ( !b ) return 0;
	
	// busca o unico vertice nao vizinho de b
	int nao_vizinho_de_b = 0, num_nao_vizinhos_de_b = 0;
	for ( i=1; i<=V(G); i++ )
		if ( G->A[b][i] == 0 && i != b ) {
			nao_vizinho_de_b = i;
			num_nao_vizinhos_de_b++;
		}
	
	// se o único vértice que não é vizinho de b não tem grau 1, então, 
	// G não é escorpião
	if ( num_nao_vizinhos_de_b != 1 || grau(G, nao_vizinho_de_b) != 1 ) return 0;

	// se o vizinho do único vértice que não é vizinho de b não tem grau 2,
	// então, G não é escorpião
	int viz; // busca o vizinho do único vértice não vizinho de b
	for ( i=1; i<=V(G); i++ )
		if ( G->A[nao_vizinho_de_b][i] == 1 )
			viz = i;
	if ( grau(G, viz) != 2 ) // se tal vértice não tem grau 2, G não é escorpião
		return 0;
	
	return 1; // as propriedades foram satisfeitas. Logo, G é escorpião
}


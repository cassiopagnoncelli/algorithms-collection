#ifndef _libescorpiao_h_
#define _libescorpiao_h_

#include <stdio.h> // usa FILE

// devolve o tamanho do conjunto de vértices
#define V(G) G->num_arestas 

typedef struct {
	int num_arestas;

	// matriz de adjacências, indexada de 1 a V(G)
	int **A; 
} grafo;


// devolve o grau do vertice no grafo
int grau(grafo *, int);

// devolve um grafo representando o mesmo grafo em arquivo de texto
grafo *recebe_grafo_adj(FILE *);

// verifica se G é escorpião
int escorpiao(grafo *);


#endif /* libescorpiao.h */


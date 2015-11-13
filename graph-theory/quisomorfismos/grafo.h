#ifndef _grafo_h_
#define _grafo_h_

#include <stdio.h>

#define V(G) (G->num_vertices)
#define E(G) (G->num_arestas)

typedef struct {
	int tam; // ordem da matriz de adjacencias
	int **A; // matriz de adjacencias
	int num_vertices, num_arestas; // cardinalidade dos conjuntos V e E
} grafo;

// cria um novo grafo
grafo *novo(int tam);

// recebe um grafo de um arquivo de texto
grafo *recebe_grafo(FILE *fp);

// devolve o conjunto de graus de cada vertice de G
int *conjunto_graus(grafo *G);

// verifica se, dado uma funcao bijetora, G e H sao isomorfos
int testa_isomorfismo(grafo *G, grafo *H, int *f);

// gera permutacoes buscando um isomorfimo de G em H
int permuta_buscando_isomorfismo(int *P, int inicio, int n, grafo *G, grafo *H);

// verifica se existe uma bijecao de G em H
int existe_bijecao(grafo *G, grafo *H);

#endif /* grafo.h */


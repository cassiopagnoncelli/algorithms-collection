#include <stdio.h>
#include "grafo.h"
//#include "basicos.h"

/* programa principal */
int main(int argc, char **argv) {
	// recebe os grafos dos arquivos e cria suas respectivas matrizes de adjacencias
	grafo *G, *H;
	if ( (argc != 3) || !(G = recebe_grafo(fopen(argv[1], "r"))) || !(H = recebe_grafo(fopen(argv[2], "r"))) ) 
		return 1; // devolve 1 ao SO em caso de parametros invalidos
	
	// se os conjuntos de vertices ou de arestas, entao, G nao eh isomorfo a H
	// obs.: por otimizacao, se os graus de G forem diferentes dos [graus] de H, entao, nao ha um isomorfismo
	if ( (V(G) != V(H)) || (E(G) != E(H)) )
		printf("0\n");
	// um caso particular, se E(G) = E(H) = 0 e V(G) = V(H), entao, existe um isomorfismo
	else if ( (V(G) == V(H)) && (E(G) == E(H)) && E(G) == 0 ) 
		printf("1\n");
	// se os conjuntos dos graus de G e H forem diferentes, entao, nao existe um isomorfismo
	else if ( !conjuntos_iguais(conjunto_graus(G), conjunto_graus(H), V(G)) ) // pois, nessa altura, V(G) = V(H)
		printf("0\n");
	// busca uma bijecao de G em H
	else
		printf("%d\n", existe_bijecao(G, H) ? 1 : 0);

	return 0; // devolve 0 ao SO
}


/** ESCORPIAO **
 *
 *    Dado um grafo G, verifica se G é um grafo escorpiao. Ou seja,
 * se as duas propriedades são satisfeitas:
 *
 *    i) existe um elemento b de V(G) tal que d(b) = |V(G)| - 2;
 *
 *   ii) o único vertice que não é vizinho de b tem grau 1 e seu
 *       vizinho tem grau 2.
 **
 */

#include "libescorpiao.h"
#include <stdio.h>

int main(int argc, char **argv) {

	// recebe a matriz de adjacencias de G
	grafo *G;
	if ( argc != 2 || !(G = recebe_grafo_adj(fopen(argv[1], "r"))) ) 
		return 1; // devolve 1 ao SO se a entrada é inválida

	// verifica se G é um grafo escorpião
	printf("%d\n", escorpiao(G));

	return 0; // devolve 0 ao SO indicando que a entrada é válida
}


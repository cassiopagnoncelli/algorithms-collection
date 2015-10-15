/** INTERFACE
 *
 *	Este programa faz a interface com a biblioteca avl-tree.h em modo texto. A
 *  biblioteca consiste de tres comandos: i (insercao), r (remocao), b (busca) em
 *  uma arvore AVL para numeros inteiros. 
 *
 */

#include "avl-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Interface da biblioteca para comandos de stdin */
int interface_stdin(void);

/* Interfaceia os comandos do arquivo de texto com a avl-tree */
int interface_arquivo(FILE *);

/* Desmembra uma string em `comando' e `valor'. Em caso de erro, devolve 0 */
int interpreta_linha(char *, char *, int *);

/* Imprime os elementos L_1,(...),L_L[0]  */
int imprime_lista(int *);


/*--- Implementacoes das funcoes [comentarios de rotinas sobre os respectivos prototipos] ---*/

int imprime_lista(int *L) { 
	if ( !L ) return 0;

	/* |L| = L[0] + 1 */
	if ( L[0] > 1 ) 
		printf("%d,", L[1]);

	int i; 
	for ( i=2; i<L[0]; i++ )
		printf("%d,", L[i]);
	
	printf("%d\n", L[L[0]]);

	return 1;
}

int interface_stdin( void ) {
	no *T = malloc(sizeof(no));
	if ( T ) inicializada(T) = 0;
	
	char 	c; 		/* comando dentre {i, r, b} */
	int 	v, 		/* parametro da {insercao, remocao, busca} */
		i=0, j=0; 	/* controle do buffer, para nao repetir strings 
			   	 * i: indica numero de comandos {i, r, b} chamados,
			   	 * j: indica o numero de impressoes.
			   	 * Portanto, sempre deve valer i=j. */
	
	do {
		scanf("%c", &c);
		switch (c) {
			case 'i':
				scanf("%d", &v);
				T = inserir(T, v);
				i++; 	/* um comando executado implica i <- i + 1,
					 * comentarios posteriormente suprimidos. */
			break;
			case 'r':
				scanf("%d", &v);
				T = balancia(remover(T, v));
				i++;
			break;
			case 'b':
				scanf("%d", &v);
				i++;
			break;
		}

		if ( c == 'i' || c == 'r' || c == 'b' )
			printf("%c %d\n", c, v);

		/* j eh o numero de iteracoes, que deve ser concordante com i, 
		 * senao, j sera decrementado posteriormente e nada sera impresso. */
		j++;

		/* previne impressoes duplicadas. */
		if ( i != j ) 
			j--;
		/* Se o comando for {insercao, remocao}, imprime a arvore */
		else if ( c != 'b' ) {
			escreve(T, PRE_ORDER);
			printf("\n");
		/* Se o comando for de busca, imprime os no's percorridos. */
		} else 
			imprime_lista(busca(T, calloc(AVL_ALTURA_MAX, sizeof(int)), v));
	} while ( c != 'q' && !feof(stdin) );

	finaliza(T); /* Destroi T. */

	return EXIT_SUCCESS;
}

int interface_arquivo(FILE *fp) {
	if ( !fp ) return EXIT_FAILURE;

	no *T = malloc(sizeof(no));
	if ( T ) inicializada(T) = 0;

	char 	comando,				/* comando dentre {i, r, b} */
		*linha = malloc(256 * sizeof(char));	/* linha que contem o `comando' e o `valor' */
	int 	valor;					/* parametro do comando */

	do {
		fgets(linha, 16, fp);
		if ( !interpreta_linha(linha, &comando, &valor) || feof(fp) ) comando = 'q';
		if ( comando != 'q' ) printf("%c %d\n", comando, valor); 
		switch (comando) {
			case 'i':
				T = inserir(T, valor);
			break;
			case 'r':
				T = balancia(remover(T, valor));
			break;
			/* Comando `b' (busca) eh tratado posteriormente ao final da iteracao, 
			 * pois a arvore nao eh impressa. 
			 */
		}

		if ( comando != 'q' && comando != 'b' ) { /* Se o comando nao for para sair, imprime a lista */
			escreve(T, PRE_ORDER);
			printf("\n");
		} else if ( comando == 'b' ) /* Se o comando for de busca, imprime os no's percorridos. */
			imprime_lista(busca(T, calloc(AVL_ALTURA_MAX, sizeof(int)), valor));
	} while ( comando != 'q' ); 

	finaliza(T); /* Destroi T. */
	
	return EXIT_SUCCESS;
}

int interpreta_linha(char *s, char *comando, int *valor) {
	if ( !s || !comando || !valor ) return 0;
	if ( strlen(s) <= 1 ) return 0;

	*comando = *s; 
	if ( *comando != 'q' ) {
		s += 2;	
		*valor = atoi(s);
	}

	return 1;
}


/* Programa principal */
int main( int argc, char *argv[] ) {
	/* Recebe comandos de stdin ou, se passado como parametro, de um arquivo de texto. */
	return argc == 1 ? interface_stdin() : interface_arquivo(fopen(argv[1], "r"));
}


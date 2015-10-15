#include "avl-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


no *inicializa (no *T, no *acima, int v) {
	if ( vazia(T) ) return NULL;

	/* Faz apenas a ligacao filho -> pai. */
	pai(T) = acima;
	
	R(T) = v;
	E(T) = D(T) = NULL;

	inicializada(T) = 1; 
	B(T) = 0;

	return T;
}

no *finaliza (no *T ) {
	if ( vazia(T) )
		return T;

	if ( folha(T) )
	{
		free(T);
		return NULL;
	}
	if ( E(T) )
		finaliza(E(T));
	if ( D(T) )
		finaliza(D(T));
	E(T) = (D(T) = NULL);
	if ( !folha(T) )
		finaliza(T);
	return T; 
}

no *raiz (no *T) {
	if ( vazia(T) ) return NULL;
	return (pai(T) ? raiz(pai(T)) : T);
}

no *balancia (no *T) {
	if ( !T ) return NULL;
	recalcula_balanceamento(T);
	if ( abs(B(T)) > 1 ) {
		if ( B(T) > 1 ) {
			if ( B(D(T)) >= 0 )
				T = rotaciona(T, ESQUERDA);
			else
				T = rotaciona(T, DIREITA_ESQUERDA);
		} else {
			if ( B(E(T)) <= 0 )
				T = rotaciona(T, DIREITA);
			else
				T = rotaciona(T, ESQUERDA_DIREITA);
		}
	}
	
	balancia(D(T));
	balancia(E(T));

	return raiz(T);
}

void recalcula_balanceamento (no * T) {
	if ( !T ) {
		return;
	}

	B(T) = h(D(T)) - h(E(T));
	recalcula_balanceamento(E(T));
	recalcula_balanceamento(D(T));
}

no *inserir (no *T, int v) {
	if ( vazia(T) ) return NULL;

	/* Busca `v' em T */
	if ( busca_no(T, v) ) return T;

	/* se encontrou uma `caixa vazia', coloca v em T e mantem T balanceada. */
	if ( !inicializada(T) ) return inicializa(T, pai(T), v);
	
	/* insercao e aloca novo no assim que necessario */
	if ( v > R(T) ) { 
		if ( !D(T) && (D(T) = inicializa(malloc(sizeof(no)), T, 0)) ) inicializada(D(T)) = 0;
		if ( inserir(D(T), v) ) B(T) = h(D(T)) - h(E(T));
		if ( B(T) >= 2 ) {
			if ( v > R(D(T)) )
				T = rotaciona(T, ESQUERDA);
			else
				T = rotaciona(T, DIREITA_ESQUERDA);
		} 
	} else if ( v < R(T) ) { 
		if ( !E(T) && (E(T) = inicializa(malloc(sizeof(no)), T, 0)) ) inicializada(E(T)) = 0;
		if ( inserir(E(T), v) ) B(T) = h(D(T)) - h(E(T));
		if ( B(T) <= -2 ) {
			if ( v < R(E(T)) )
				T = rotaciona(T, DIREITA);
			else
				T = rotaciona(T, ESQUERDA_DIREITA);
		}
	} 

	B(T) = h(D(T)) - h(E(T));

	return T;
}

int remove_raiz(no *T)
{
	no *maior_men=maior(E(T));

	if ( !vazia(E(maior_men)) )
		pai(E(maior_men))=pai(maior_men);

	if ( E(pai(maior_men)) == maior_men )
		E(pai(maior_men))=E(maior_men);
	else
		D(pai(maior_men))=E(maior_men);
	
	R(T)=R(maior_men);
	free (maior_men);
	return 0;
}


no *remover (no *T, int v) {
	if ( vazia(T) ) return NULL;
	no *ocorrencia = busca_no(T, v);
	if ( !ocorrencia ) return raiz(T);
	T = ocorrencia;

	/* R(T) = v. */
	if ( folha(T) ) {
		no *p = pai(T);
		if ( pai(T) ) { 
			pai_filho(pai(T), NULL, ((R(T) > R(pai(T))) ? DIREITA : ESQUERDA));
			free(T);
			T = p;
		} else
			inicializada(T) = 0;
	} else if ( !D(T) || !E(T) ) { /* T tem apenas um filho */
		no *r = raiz(T);
		if ( pai(T) ) {
			pai_filho(pai(T), (D(T) ? D(T) : E(T)), ESQUERDA); /* direcao tanto faz. */
			free(T);
			return pai(r) ? raiz(r) : r;
		} else {
			r = (D(T) ? D(T) : E(T));
			free(T);
			pai_filho(NULL, r, ESQUERDA); /* direcao tanto faz. */
			return pai(r) ? raiz(r) : r;
		}
	} else { /* Remove caso dois filhos */
		remove_raiz(T);
		T = balancia(T);
	}
	return T;
}

int *busca (no *T, int *L, int v) {
	if ( vazia(L) ) return NULL;
	if ( vazia(T) ) return L;

	if ( inicializada(T) ) L[ ++L[0] ] = R(T); /* R(T) ao final de L. */

	if ( R(T) == v ) 
		return L;
	else if ( v > R(T) )
		return busca(D(T), L, v);
	else 
		return busca(E(T), L, v);
}

no *busca_no (no * T, int v) {
	if ( vazia(T) ) return NULL;
	if ( !inicializada(T) ) return NULL;
	if ( v == R(T) ) return T;
	else if ( v > R(T) ) return busca_no(D(T), v);
	else return busca_no(E(T), v);
}

no *rotaciona (no *T, enum direcao_e direcao) {
	if ( vazia(T) ) return NULL;

	switch (direcao) {
		/* Faz D(A=T) virar raiz de T:
		 * 
		 *         K                             K  
		 *         A                             B
		 *   X           B        --\	   A          C
		 *             Y   C      --/    X   Y 
		 *
		 * onde K, X, Y podem nao existir e pai(A) = K.
		 */
		case ESQUERDA: {
			/* se B nao existe, a rotacao eh impossivel. */
			if ( vazia(D(T)) ) return T; 

			no 	*K = pai(T),
				*Y = D(T) ? E(D(T)) : NULL; /* para evitar SEGFAULT */

			/* tenta fazer B pai de A [A filho esquerdo de B] */
			if ( !pai_filho(D(T), T, ESQUERDA) ) return T; 
			T = pai(T); /* pois T deve apontar para B (e nao mais para A) */
			
			/* tenta fazer A pai de Y [Y filho direito de A], se Y existir */
			pai_filho(E(T), Y, DIREITA);
			/* faz K pai de B (=T novo) [a direcao nao importa, pai_filho() identifica. */
			pai_filho(K, T, DIREITA);

			/* recalcula os balanceamentos */
			B(E(T)) = h(D(E(T))) - h(E(E(T)));
			K = E(T);
			while ( (K=pai(K)) )
				B(K) = h(D(K)) - h(E(K));
			
			return T;
		} break;

		/* Simetrico a rotacao para esquerda,
		 * mantendo as notacoes A < B < C, pai(T) = K e pai(Y) = B.
		 */
		case DIREITA: {
			if ( vazia(E(T)) ) return T; 

			no 	*K = pai(T),
				*Y = E(T) ? D(E(T)) : NULL; 

			if ( !pai_filho(E(T), T, DIREITA) ) return T; 
			T = pai(T); 
			
			pai_filho(D(T), Y, ESQUERDA);
			pai_filho(K, T, ESQUERDA);

			B(D(T)) = h(D(D(T))) - h(E(D(T)));
			K = D(T);
			while ( (K=pai(K)) )
				B(K) = h(D(K)) - h(E(K));

			return T;
		} break;

		/* Faz uma rotacao para esquerda no filho esquerdo
		 * seguida de uma rotacao para direita. 
		 */
		case ESQUERDA_DIREITA: {
			E(T) = rotaciona(E(T), ESQUERDA);
			T = rotaciona(T, DIREITA);
			return T;
		} break;

		/* Simetrico a rotacao ESQUERDA_DIREITA
		 */
		case DIREITA_ESQUERDA: {
			D(T) = rotaciona(D(T), DIREITA);
			T = rotaciona(T, ESQUERDA);
			return T;
		} break;
	}

	return T;
}


int pai_filho (no * pai, no * filho, enum direcao_e direcao) {
	if ( vazia(pai) && vazia(filho) ) 
		return 0;
	else if ( vazia(pai) ) {
		pai(filho) = NULL;
		return 1;
	} else if ( vazia(filho) ) {
		(direcao == DIREITA) ? (D(pai) = NULL) : (E(pai) = NULL);
		return 1;
	} else {
		/* escolhe o no' do pai para o qual aponta para filho e pai(filho)
		 * apontar para pai. */
		(R(filho) > R(pai)) ? (D(pai) = filho) : (E(pai) = filho);
		pai(filho) = pai;

		return 1;
	} 
}

void escreve (no * T, enum ordem_e ordem) {
	if ( vazia(T) ) { printf("()"); return; }
	if ( !inicializada(T) ) { printf("()"); return; }

	switch (ordem) {
		case PRE_ORDER:
			/* Ordem: R(T), E(T), D(T) */
			printf("(%d,", R(T));
			escreve(E(T), PRE_ORDER);
			printf(",");
			escreve(D(T), PRE_ORDER);
			printf(")");
		break;
		case POST_ORDER:
			/* Ordem: E(T), D(T), R(T) */
			printf("(");
			escreve(E(T), POST_ORDER);
			printf(",");
			escreve(D(T), POST_ORDER);
			printf(",%d)", R(T));
		break;
		default:
			/* Ordem: E(T), R(T), D(T) */
			printf("(");
			escreve(E(T), IN_ORDER);
			printf(",%d,", R(T));
			escreve(D(T), IN_ORDER);
			printf(")");
		break;
	}
}

int h (no *T) {
	if ( vazia(T) )
	{
		return 0;
	}
	return 1 + max(h(E(T)), h(D(T)));
}

no *maior (no * T) {
	if ( !T ) return NULL;
	return D(T) ? maior(D(T)) : T;
}

no *menor (no * T) {
	if ( !T ) return NULL;
	return E(T) ? menor(E(T)) : T;
}

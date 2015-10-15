/** AVL **
 *
 * 	Biblioteca basica para manipulacao de arvores AVL.
 *
 ** Juan Manuel Sanchez Ruibal,	jmsr07 EM inf PONTO ufpr PONTO br
 ** Ronnie Francis Dilli 	rfd06 EM inf PONTO ufpr PONTO br
 */

#ifndef _avl_tree_h_
# define _avl_tree_h_

/* Definicao de no' */
typedef struct no_t no;
struct no_t
{
  int init; /* indica se T esta inicializada */

  int r, /* Raiz */
      b; /* Balanceamento */

  /* Filhos esquero e direito */
  struct no_t *e;
  struct no_t *d;

  /* Pai de T */
  struct no_t *pai;
};

#define AVL_ALTURA_MAX 32	/* Vamos supor que a arvore nao tera mais do que 2^31-1 elementos */

/* Ordem de impressao */
enum ordem_e
{
  PRE_ORDER,
  POST_ORDER,
  IN_ORDER
};

/* Direcao da rotacao */
enum direcao_e
{
  DIREITA,
  ESQUERDA,
  DIREITA_ESQUERDA,
  ESQUERDA_DIREITA
};


#define pai(T) T->pai 		/* Pai de T */
#define E(T) T->e 		/* Filho esquerdo de T */ 
#define D(T) T->d 		/* Filho direito de T */
#define R(T) T->r 		/* Raiz de T */
#define B(T) T->b 		/* Balanceamento de T */
#define vazia(T) (T == NULL) 	/* Verifica se T eh vazia [nao alocada] */
#define inicializada(T) T->init	/* Flag de inicializacao de T */
#define max(a, b) (a>b ? a : b)	/* Maior dentre {a, b} */
#define min(a, b) (a<b ? a : b)	/* Menor dentre {a, b} */
#define folha(T) ( vazia(E(T)) && vazia(D(T)) ) /* Verifica se T eh folha */


/* Inicializa T com `v' e como filho de `acima'. 
 * Devolve uma referencia para T ou NULL, se T for vazia. */
no *inicializa (no * T, no * acima, int v);

/* Destroi todas as subarvores de T e devolve T como folha. */
no *finaliza (no * T);

/* Devolve a raiz de T, se T for valido. */
no *raiz (no * T);

/* Balancia a arvore T e suas sub-arvores.
 * Devolve raiz de T em todo caso. */
no *balancia (no * T);

/* Recalcula o balanceamento de T e suas sub-arvores [modo forçado] */
void recalcula_balanceamento (no * T);

/* Coloca `v' em T caso `v' nao esteja em T.
 * Devolve T em todo caso. */
no *inserir (no * T, int v);

/* Remove T quando for raiz de subarvore, ou seja, com dois filhos */
int remove_raiz(no *T);

/* Remove v de T mantendo T balanceada. */
no *remover (no * T, int v); 

/* Faz uma busca de `v' em T e guarda o caminho em L, 
 * na ocasiao de `v' estar em T, L[L[0]] = v.
 * Devolve a lista dos no's percorridos. */
int *busca (no * T, int * L, int v);

/* Busca o no' cuja raiz eh v. 
 * Devolve a referencia para v se encontrou, caso contrario uma referencia nula. */
no *busca_no (no * T, int v); 

/* Rotaciona uma arvore T em quatro sentidos: esquerda, direita, 
 * esquerda-direita e direita-esquerda.
 * Devolve a raiz do no' rotacionado. */
no *rotaciona (no * T, enum direcao_e direcao);

/* Dado A e B arvores, faz A ser pai de B e B ser filho de A e tenta
 * fazer com que B esteja à `direcao' de A.
 * Devolve 1 se a permutacao teve sucesso, caso contrario 0. */
int pai_filho (no * pai, no * filho, enum direcao_e direcao);

/* Escreve a arvore em PRE_ORDER, IN_ORDER ou POST_ORDER */
void escreve (no * T, enum ordem_e ordem);

/* Calcula e devolve a altura de T */
int h (no * T);

/* Devolte uma referencia para o maior elemento de T */
no *maior (no * T);

/* Devolve uma referencia para o menor elemento de T */
no *menor (no * T);


#endif /* avl-tree.h */


#ifndef _basicos_h_
#define _basicos_h_

// troca o conteudo dos elementos
void troca(int *, int *);

// calcula n!
int fatorial(int);

// imprime uma permutacao com elementos separados por espacos e limitados por < e >
void imprime_permutacao(int *P, int n);

// imprime M indexada de l_a ate l_b para linhas e c_a e c_b para colunas
void imprime_matriz(int **M, int l_a, int l_b, int c_a, int c_b); 

// dados dois conjuntos tais que |A| = |B|, verifica se A = B
int conjuntos_iguais(int *A, int *B, int tam);

// rotina do quicksort para particionamento
int particiona(int *V, int inicio, int fim); 

// ordena um vetor indexado de `a' a `b' com o metodo da divisao-e-conquista por quicksort
void quicksort(int *V, int a, int b);

#endif /* basicos.h */

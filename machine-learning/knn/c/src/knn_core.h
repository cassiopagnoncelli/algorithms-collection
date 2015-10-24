/*
  Biblioteca do programa que implementa o classificador k-NN.
*/
#ifndef knn_core
#define knn_core

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <list>

using namespace std;

/* Cria uma nova matriz quadrada de inteiros de ordem `dimensao', preenche-a
   com zero e a devolve. */
int **
nova_matriz_quadrada(int dimensao);

/* Mensagem de erro. */
int
erro_msg(string str);

/* Estrutura `base'. */
typedef struct base_t {
  /* matriz e suas dimensões */
  int lins, cols;
  double **matriz;

  /* classe à qual pertence o elemento que corresponde à linha da matriz. */
  int *classe;
} base;

/* Normaliza os dados num intervalo de 0 a 1, relativos ao
   máximo e mínimo, que são respectivamente 0 e 1. */
void
normalizar_dados(base *b);

/* Carrega uma amostra de um arquivo devolvendo uma estrutura contendo:
   - uma matriz, onde cada linha é o vetor de características
   - as dimensões da matriz
   - um vetor que indica qual à qual classe pertence o respectivo elemento
     da matriz.
*/
base *
carrega(FILE *fp, int normalizar);

/* Busca o número de classes distintas em uma base. */
int
busca_num_classes(base *x, int normalizar);

/*
  Algoritmo k-NN.

    Classifica todos os pontos da base de teste, `testing', segundo a classe
  mais frequente na ordenação das `k' primeiras distâncias para cada um dos
  pontos da base de treinamento, `training'.

    Como resultado, o algoritmo k-NN produz uma matriz de confusão, indicando a
  qualidade de cada uma das características, e a taxa de acerto
  (0 <= acerto <= 1) que o classificador teve.

    Um particular ponto da amostra de teste `testing' é classificado pelo "core"
  do k-NN, `classifica_ponto'. Em decorrência dessa classificação ser dada pelas
  menores distâncias e a respectiva classe associada à cada uma dessas
  distâncias, uma nova estrutura é usada para fazer concretizar essa associação,
  `aresta'.
*/
/* Estrutura `aresta', previamente citada. */
typedef struct /*aresta_t*/ {
  double d;
  int classe;
} aresta;

/* Cria uma nova aresta entre dois pontos. Essa aresta contém a informação
   da distância entre esses dois pontos e a classe à qual o ponto sob inspeção
   é candidato a pertencer. */
aresta *
nova_aresta(double d, int classe);

/* Devolve o comprimento (=distância) da aresta x. */
inline double
comprimento(aresta *x);

/* Função de comparação entre duas arestas.*/
int
compara_aresta(aresta *x, aresta *y);

/* Busca a posição para inserir `x' na lista de arestas (insertion-sort). */
void
busca_pos_insercao(list<aresta*> *arestas, aresta *x);

/* Insere `x' na lista mantendo a ordem. */
void
insercao_ordenada(list<aresta*> *arestas, aresta *x);

/* Insere `x' no `vetor' se `x' pode substituir alguma outra aresta de `vetor'
   por ter menor distância. */
int
insere_classes_frequentes(list<aresta*> *arestas, aresta *x);

/* Determina a classe mais frequente dentre um conjunto de classes. */
int
classe_mais_frequente(list<aresta*> *arestas);

/* 
   Cálculo da distância entre os pontos `p1' e `p2', ambos de mesma dimensão. 
   Abordagens disponíveis (configure no Makefile):
   - Manhattan
   - Chebyschev
   - Minkowski [exige o parâmetro `p', definido no Makefile]
   - euclidiana (padrão)
*/
#if defined MANHATTAN /* distância Manhattan */
#define METODO_DISTANCIA "Manhattan"
double
distancia(double *p1, double *p2, int dimensao);
#elif defined CHEBYSCHEV /* distância Chebyschev */
#define METODO_DISTANCIA "Chebyschev"
double
distancia(double *p1, double *p2, int dimensao);
#elif defined MINKOWSKI /* distância Minkowski */
#define METODO_DISTANCIA "Minkowski"
double
distancia(double *p1, double *p2, int dimensao);
#else /* distância euclidiana (padrão) */
#define METODO_DISTANCIA "euclidiana"
double
distancia(double *p1, double *p2, int dimensao);
#endif

/* Trata-se do "core" do algoritmo k-NN. É o classificador de um dado ponto pela
   classe mais frequente dentre os k pontos com menor distância para o ponto em
   questão, e usa `training' como base de treinamento. */
int
classifica_ponto(int k, base *training, double *ponto);

/* Algoritmo k-NN, conforme descrito anteriormente. */
int
knn(base *training, base *testing, int k);

/*
  Apenas devolve a taxa de acerto do k-NN para a base `testing' treinada
  com a base `training' e parâmetro-k.
*/
double
knn_taxa(base *training, base *testing, int k);

#endif /* knn_core.h */

/*
   Implementação do classificador k-NN (k-nearest neighbor).
*/
#include "knn_core.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <list>

using namespace std;

/*
  Coletor de lixo das variáveis alocadas
*/
struct lixo_t {
  /* matrizes quadradas */
  list<int**> matriz_quadrada;
  list<int> matriz_quadrada_n;

  /* arestas */
  list<aresta *> cjto_arestas;
  
  /* frequencia das classes */
  list<int *> cjto_freq_classes;
} lixo;

void coleta_lixo(int **matriz, int ordem)
{
  lixo.matriz_quadrada.push_back(matriz);
  lixo.matriz_quadrada_n.push_back(ordem);
}

void coleta_lixo(aresta *a)
{
  lixo.cjto_arestas.push_back(a);
}

void coleta_lixo(int *classes)
{
  lixo.cjto_freq_classes.push_back(classes);
}

void esvazia_lixo()
{
  /* esvazia matriz */
  list<int**>::iterator it_intpp;
  list<int>::iterator it_int;
  for (it_intpp = lixo.matriz_quadrada.begin(), 
	 it_int = lixo.matriz_quadrada_n.begin();
       it_intpp != lixo.matriz_quadrada.end() &&
	 it_int != lixo.matriz_quadrada_n.end(); it_intpp++, it_int++) {
    delete [] (*it_intpp)[0];
    delete [] (*it_intpp);
  }

  /* esvazia arestas */
  /*list<aresta*>::iterator it_aresta;
  for (it_aresta = lixo.cjto_arestas.begin(); 
  it_aresta != lixo.cjto_arestas.end(); it_aresta++);*/

  /* esvazia classes */
  list<int*>::iterator it_intp;
  for (it_intp = lixo.cjto_freq_classes.begin();
       it_intp != lixo.cjto_freq_classes.end(); it_intp++) {
    delete [] (*it_intp);
  }
}


/* Cria uma nova matriz quadrada de inteiros de ordem `dimensao', preenche-a
   com zero e a devolve. */
int **
nova_matriz_quadrada(int dimensao)
{
  /* aloca matriz */
  int **matriz = new int*[dimensao];
  matriz[0] = new int[dimensao * dimensao];

  /* ajusta os ponteiros */
  int i;
  for (i = 1; i < dimensao; ++i)
    matriz[i] = matriz[i-1] + dimensao;

  /* preenche com zeros */
  int j;
  for (i = 0; i < dimensao; i++)
    for (j = 0; j < dimensao; j++)
      matriz[i][j] = 0;

  
  coleta_lixo(matriz, dimensao); /* marca coleta de lixo */

  return matriz;
}

/* Mensagem de erro. */
int
erro_msg(string str)
{
  cout << str << endl;
  return EXIT_FAILURE;
}

/* Normaliza os dados num intervalo de 0 a 1, relativos ao
   máximo e mínimo, que são respectivamente 0 e 1. */
void
normalizar_dados(base *b)
{
  register double min, max;
  int c, i; /* característica */
  for (c = 0; c < b->cols; c++) { /* itera sobre a coluna */
    /* descobre os valores mínimo e máximo da coluna */
    min = 1000000000.0;
    max = 0;
    for (i = 0; i < b->lins; i++) {
      if (b->matriz[c][i] < min)
	min = b->matriz[c][i];
      if (b->matriz[c][i] > max)
	max = b->matriz[c][i];
    }

    /* x* = (x - min) / (max - min) */
    for (i = 0; i < b->lins; i++)
      b->matriz[c][i] = (b->matriz[c][i] - min) / (max - min);
  }
}

/* Carrega uma amostra de um arquivo devolvendo uma estrutura contendo:
   - uma matriz, onde cada linha é o vetor de características
   - as dimensões da matriz
   - um vetor que indica qual à qual classe pertence o respectivo elemento
     da matriz.
*/
base *
carrega(FILE *fp, int normalizar)
{
  if (!fp)
    return NULL;

  /* informações do arquivo contendo as dimensões da matriz */
  int num_linhas, num_caracteristicas;
  if (fscanf(fp, "%d %d", &num_linhas, &num_caracteristicas) <= 0) {
    erro_msg("A primeira linha do arquivo deve informar o tamanho da amostra \
e a quantidade de características.");
    return NULL;
  }

  /* prepara a estrutura que irá conter a amostra */
  base *b = new base;

  int i;
  b->matriz = new double*[num_linhas];
  b->matriz[0] = new double[num_linhas * num_caracteristicas];
  for (i = 1; i < num_linhas; ++i)
    b->matriz[i] = b->matriz[i-1] + num_caracteristicas;

  b->classe = new int[num_linhas];

  b->lins = num_linhas;
  b->cols = num_caracteristicas;

  /* carrega os dados para a estrutura `base' */
  int j;
  for (i=0; i<num_linhas && fgetc(fp); i++) {
    for (j=0; j<num_caracteristicas; j++)
      if (fscanf(fp, "%lf ", &b->matriz[i][j]) <= 0) {
        erro_msg("O arquivo está em formato inválido ou é vazio.");
        return NULL;
      }

    if (fscanf(fp, "%d", &b->classe[i]) <= 0) {
      erro_msg("O arquivo está em formato inválido ou é vazio.");
      return NULL;
    }
  }

  if (normalizar)
    normalizar_dados(b);
  
  return b;
}

/* Busca o número de classes distintas em uma base. */
int
busca_num_classes(base *x)
{
  int i, max = -1;
  
  /* percorre a base `x' */
  for (i = 0; i < x->lins; i++)
    if (max < x->classe[i])
      max = x->classe[i];

  return max + 1;
}

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
/* Cria uma nova aresta entre dois pontos. Essa aresta contém a informação
   da distância entre esses dois pontos e a classe à qual o ponto sob inspeção
   é candidato a pertencer. */
aresta *
nova_aresta(double d, int classe)
{
  aresta *a = /*new aresta*/ (aresta *) malloc(sizeof(aresta));

  a->d = d;
  a->classe = classe;

  coleta_lixo(a); /* marca coleta de lixo */

  return a;
}

/* Devolve o comprimento (=distância) da aresta x. */
inline double
comprimento(aresta *x) {
  return x->d;
}

/* Função de comparação entre duas arestas.*/
int
compara_aresta(aresta *x, aresta *y) {
  if (x->d < y->d)
    return -1;

  if (x->d > y->d)
    return 1;

  return 0;
}

/* Busca a posição para inserir `x' na lista de arestas (insertion-sort). */
void
busca_pos_insercao(list<aresta*> *arestas, aresta *x)
{
  /* ** ASSUMIREMOS QUE A LISTA TEM MAIS DE UM ELEMENTO **
     A função

                   { P_0,             se i = 0;
     pos(P_i, x) = { P_i,             se x <= |P_i|;
                   { pos(P_{i+1}, x), se |P_{i}| < x.
     
     descreve o lugar correto para inserir `x' no vetor `arestas'.
  */
  list<aresta*>::iterator i;
  for (i = (*arestas).begin(); i != (*arestas).end(); ++i)
    if (comprimento(x) < comprimento(*i)) {
      (*arestas).insert(i, x);
      return;
    }
}

/* Insere `x' na lista mantendo a ordem. */
void
insercao_ordenada(list<aresta*> *arestas, aresta *x)
{
  if ((*arestas).empty()) { /* lista vazia */
    (*arestas).push_back(x);
    return;
  }

  if ((*arestas).size() == 1) { /* lista unitária */
    if (comprimento((*arestas).back()) < comprimento(x))
      (*arestas).push_back(x);
    else
      (*arestas).push_front(x);
  } else /* lista com mais de um elemento */
    busca_pos_insercao(arestas, x);
}

/* Insere `x' no `vetor' se `x' pode substituir alguma outra aresta de `vetor'
   por ter menor distância. */
int
insere_classes_frequentes(list<aresta*> *arestas, aresta *x)
{
  if (comprimento((*arestas).back()) < comprimento(x))
    return 1;

  insercao_ordenada(arestas, x);
  (*arestas).pop_back();

  return 1;
}

/* Determina a classe mais frequente dentre um conjunto de classes. */
int
classe_mais_frequente(list<aresta*> *arestas)
{
  /* constroi um histograma com comprimento dado pela diferença
     entreas classes de menor e maior índices */
  int
    minimo = 10000,
    maximo = -1;

  list<aresta*>::iterator it;
  for (it = (*arestas).begin(); it != (*arestas).end(); ++it) {
    if ((*it)->classe < minimo)
      minimo = (*it)->classe;

    if ((*it)->classe > maximo)
      maximo = (*it)->classe;
  }

  int *freq_classes = new int[maximo - minimo + 1];

  int i;
  for (i = 0; i < maximo - minimo + 1; i++)
    freq_classes[i] = 0;

  for (it = (*arestas).begin(); it != (*arestas).end(); ++it)
    freq_classes[(*it)->classe - minimo]++;

  /* busca pela classe com maior valor no histograma */
  int classe_frequente = -1, classe_ocorrencia = 0;
  for (i = 0; i < maximo - minimo + 1; i++)
    if (freq_classes[i] > classe_ocorrencia) {
      classe_ocorrencia = freq_classes[i];
      classe_frequente = i;
    }

  delete [] freq_classes; /* desaloca memória */
  return minimo + classe_frequente; /* índice deslocado para a classe real */
}

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
distancia(double *p1, double *p2, int dimensao)
{
  double d = 0; /* distância */
  
  int i;
  for (i = 0; i < dimensao; i++)
    d += fabs(p1[i] - p2[i]);

  return d;
}
#elif defined CHEBYSCHEV /* distância Chebyschev */
#ifndef METODO_DISTANCIA
#define METODO_DISTANCIA "Chebyschev"
#endif
double
distancia(double *p1, double *p2, int dimensao)
{
  double max = 0.0;
  
  int i;
  for (i = 0; i < dimensao; i++)
    if (max < fabs(p1[i] - p2[i]))
      max = fabs(p1[i] - p2[i]);

  return max;
}
#elif defined MINKOWSKI /* distância Minkowski */
#ifndef METODO_DISTANCIA
#define METODO_DISTANCIA "Minkowski"
#endif
double
distancia(double *p1, double *p2, int dimensao)
{
  int minkowski_p = MINKOWSKI;

  double d = 0.0;

  int i;
  for (i = 0; i < dimensao; i++)
    d += pow(fabs(p1[i] - p2[i]), minkowski_p);

  return pow(d, static_cast<double>(1) / static_cast<double>(minkowski_p));
}
#else /* distância euclidiana (padrão) */
#ifndef METODO_DISTANCIA
#define METODO_DISTANCIA "euclidiana"
#endif
double
distancia(double *p1, double *p2, int dimensao)
{
  double d = 0; /* distância */

  int i;
  for (i = 0; i < dimensao; i++)
    d += pow(p1[i] - p2[i], 2);

  return sqrt(d);
}
#endif

/* Trata-se do "core" do algoritmo k-NN. É o classificador de um dado ponto pela
   classe mais frequente dentre os k pontos com menor distância para o ponto em
   questão, e usa `training' como base de treinamento. */
int
classifica_ponto(int k, base *training, double *ponto)
{
  /*
    (ESSE É UM PONTO CRÍTICO DO PROBLEMA, RESPONSÁVEL PELO ALTO CUSTO
    COMPUTACIONAL ASSOCIADO.)

    Estrutura otimizada que reduz a complexidade computacional do caso médio do
    problema. Ao invés ordenar todos os `training->lins' pontos com custo
    esperado de O(training->lins * log(training->lins)), tentamos colocar as
    arestas no vetor de arestas, que é limitado pela constante `k'. Assim,
    teremos no máximo k * training->lins comparações e um custo esperado de
    O(training->lins * lg k).
  */
  list<aresta*> *arestas = new list<aresta*>;

  int i;
  for (i = 0; i < k; i++)
    insercao_ordenada(
      arestas, 
      nova_aresta(distancia(training->matriz[i], ponto, training->cols),
                  training->classe[i]));

  for (i = k; i < training->lins; i++)
    if (!insere_classes_frequentes(
	   arestas,
           nova_aresta(
	     distancia(training->matriz[i], ponto, training->cols), 
	     training->classe[i])))
      return -1;

  int cmf = classe_mais_frequente(arestas);
  delete arestas;
  return cmf;
}

/* Algoritmo k-NN, conforme descrito anteriormente. */
int
knn(base *training, base *testing, int k)
{
  /* classificação dada pelo k-NN para cada um dos elementos da amostra. */
  int *classificacao_amostra = new int[testing->lins];

  /* quantidade de acertos */
  int acertos = 0;

  /* matriz de confusão (alocação e inicialização) */
  int num_classes = busca_num_classes(training);
  int **confusao = nova_matriz_quadrada(num_classes);
  
  /* classifica cada um dos pontos da base de teste `testing' */
  int i;
  for (i = 0; i < testing->lins; i++)
  {
    classificacao_amostra[i] = 
      classifica_ponto(k, training, testing->matriz[i]);
    
    /* marca acertos e não marca erros */
    if (classificacao_amostra[i] == testing->classe[i])
      acertos++;
    
    /* marca a matriz de confusão */
    confusao[classificacao_amostra[i]][testing->classe[i]]++;
  }

  /* cálculo da taxa de acerto é dada por

         c/t,

     onde
       c: qtde de pontos classificados corretamente
       t: qtde de pontos submetidos à classificação
   */
  double taxa_acerto = 
    static_cast<double>(acertos) / static_cast<double>(testing->lins);

  /* 
     Resultados do k-NN:
     - taxa de acerto: impressa na saída padrão
     - matriz de confusão: 
   */
  cout << "Resultado do teste k-NN usando k=" << k << endl << endl;

  cout << "Abordagem* no cálculo da distância entre dois pontos: " << endl
       << "\t" << "distância " << METODO_DISTANCIA << endl << endl;

  cout << "Taxa de acerto: " << endl << "\t" << taxa_acerto
       << "   (=" << acertos << "/" << testing->lins << ")" << endl << endl;

  cout << "Matriz** de confusão [" << num_classes << " classes encontradas]: "
       << endl;

  int j;
  for (i = 0; i < num_classes; i++) {
    for (j = 0; j < num_classes; j++)
      cout << confusao[i][j] << "\t";
    cout << endl;
  }

  cout << endl << "*  Para usar outro método é necessária recompilação."
       << endl << "   Como esse é um ponto crítico em termos de performance,"
       << endl << "   a função não deve ser determinada dinamicamente; por"
       << endl << "   isso, o método deve ser especificado em tempo de"
       << endl << "   compilação, via `Makefile'. Os métodos disponíveis são: "
       << endl << "   - distância Manhattan"
       << endl << "   - distância Chebyschev"
       << endl << "   - distância Minkowski (paramétrica)"
       << endl << "   - distância euclidiana"
       << endl << "   Para saber mais, veja LEIAME." << endl;

  cout << endl << "** Um elemento da amostra contado na posição M[lin][col]"
       << endl << "   representa que o k-NN classificou tal elemento como sendo"
       << endl << "   pertinente à classe `lin' enquanto seu registro aponta"
       << endl << "   como sendo da classe `col'." << endl;

  /* desaloca memória */
  delete [] classificacao_amostra;

  return 1; /* retorno OK. */
}

/*
  Apenas devolve a taxa de acerto do k-NN para a base `testing' treinada
  com a base `training' e parâmetro-k.
*/
double
knn_taxa(base *training, base *testing, int k)
{
  /* classificação dada pelo k-NN para cada um dos elementos da amostra. */
  int *classificacao_amostra = new int[testing->lins];

  int acertos = 0; /* quantidade de acertos */

  /* classifica cada um dos pontos da base de teste `testing' */
  int i;
  for (i = 0; i < testing->lins; i++)
  {
    classificacao_amostra[i] = 
      classifica_ponto(k, training, testing->matriz[i]);
    
    /* marca acertos e não marca erros */
    if (classificacao_amostra[i] == testing->classe[i])
      acertos++;
  }

  delete [] classificacao_amostra;
  esvazia_lixo();
  return static_cast<double>(acertos) / static_cast<double>(testing->lins);
}

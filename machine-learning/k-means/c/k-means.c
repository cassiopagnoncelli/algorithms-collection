/*
  ** k-means **
  
  
  
  --
  Cássio Jandir Pagnoncelli, kimble9t (em) gmail (ponto) com
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <alloca.h>

#define ERRO 0.000001

/* mensagem de erro. */
int
erro(const char *str)
{
  fprintf(stderr, "%s.\n", str);
  return EXIT_FAILURE;
}

/* pontos */
typedef struct ponto_t {
  double x, y;
} ponto;

ponto *
novo_ponto(double x, double y)
{
  ponto *p = malloc(sizeof(ponto));
  p->x = x;
  p->y = y;

  return p;
}

typedef struct espaco_pontos_t {
  ponto **vetor;
  unsigned int tam;
} espaco_pontos;

/* distancia */
double
dist(ponto *a, ponto *b)
{
  /*return (fabs(a->x - b->x) + fabs(a->y - b->y));*/
  return sqrt((a->x - b->x) * (a->x - b->x)
	      + (a->y - b->y) * (a->y - b->y));
}

/* principal. */
int
main(int argc, char **argv)
{
  if (argc != 3)
    return erro("Os únicos e obrigatórios argumentos são o caminho para um \
arquivo de pontos e o valor de k (um inteiro positivo)");

  /* Lê pontos */
  FILE *fp = fopen(argv[1], "r");
  if (!fp)
    return erro("Não consegui abrir o arquivo");

  espaco_pontos tabela;
  if (fscanf(fp, "%u", &(tabela.tam)) == -1)
    return erro("O formato do arquivo parece estar incorreto");

  if (!(tabela.vetor = malloc(tabela.tam * sizeof(ponto))))
    return erro("Não consegui alocar memória para todos os pontos");

  printf("Lendo pontos... ");
  double x, y;
  unsigned int i;
  for (i=0; i<tabela.tam; i++) {
    fscanf(fp, "%lf %lf\n", &x, &y);
    tabela.vetor[i] = novo_ponto(x, y);
    /*printf("(%f, %f)\n", tabela.vetor[i]->x, tabela.vetor[i]->y);*/
  }
  printf("OK\n");
  
  /* Calcula centróides */
  srand(500);
  unsigned int k = (unsigned int) atoi(argv[2]);
  ponto **centroides = malloc(k * sizeof(ponto *));
  for (i=0; i<k; i++) {
    centroides[i] = novo_ponto((double)(rand() % 100), (double)(rand() % 100));
    /*printf("centroide %u: (%f, %f)\n", i, centroides[i]->x, centroides[i]->y);*/
  }

  /* k-means */
  unsigned int *classes_dos_pontos = alloca(tabela.tam * sizeof(unsigned int));
  if (!classes_dos_pontos)
    return erro("Não consegui alocar memória para as classes dos pontos");
  
  unsigned int j, min, num_pontos, centroides_mudaram;
  do {
    /* classifica os pontos de acordo com o centroide mais próximo */
    for (i=0; i<tabela.tam; i++)
    {
      min = 0;
      for (j=0; j<k; j++)
	if (dist(tabela.vetor[i], centroides[j]) < dist(tabela.vetor[i], centroides[min]))
	  min = j;

      classes_dos_pontos[i] = min;
    }

    /* recalcula cada centroide */
    centroides_mudaram = 0;
    for (i=0; i<k; i++)
    {
      num_pontos = 0;
      x = 0; y = 0;
      for (j=0; j<tabela.tam; j++) {
	if (classes_dos_pontos[j] == i) {
	  num_pontos++;
	  x += tabela.vetor[j]->x;
	  y += tabela.vetor[j]->y;
	}
      }

      x = (double) (x / ((double) (num_pontos)));
      y = (double) (y / ((double) (num_pontos)));

      /* verifica se a centróide mudou */
      if (fabs(centroides[i]->x - x) > ERRO
	  && fabs(centroides[i]->y - y) > ERRO)
	centroides_mudaram = 1;

      /* atualiza valor da centroide */
      free(centroides[i]);
      centroides[i] = novo_ponto(x, y);
    }
  } while (centroides_mudaram);

  /* imprime centroides */
  for (i=0; i<k; i++) {
    printf("centroide %u: (%lf, %lf)\n", i, centroides[i]->x, centroides[i]->y);
  }
  
  return EXIT_SUCCESS;
}

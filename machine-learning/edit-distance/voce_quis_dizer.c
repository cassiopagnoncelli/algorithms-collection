#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "edit_distance.h"

#define MAX_PALAVRAS 1000

/* estrutura que contém o par (palavra, distância(base, palavra)). */
typedef struct dist_t {
  char palavra[BUFSIZ];
  unsigned int distancia;
} dist;

dist *nova_dist(char *pal, unsigned int d)
{
  dist *novo = malloc(sizeof(dist));
  if (!novo)
    return NULL;

  memcpy(novo->palavra, pal, strlen(pal) + 1);
  novo->distancia = d;

  return novo;
}

int
compara_dist(const void *d1, const void *d2)
{
  const dist *p1 = (const dist *) d1;
  const dist *p2 = (const dist *) d2;
  /*return strcmp(p1->palavra, p2->palavra);*/
  return p1->distancia < p2->distancia ? -1 : (p1->distancia == p2->distancia ? 0 : 1);
}

/* quicksort */
void
troca(dist *x, dist *y)
{
  /* temp <- x */
  char palavra[BUFSIZ];
  memcpy(palavra, x->palavra, 1 + strlen(x->palavra));
  unsigned distancia = x->distancia;

  /* x <- y */
  memcpy(x->palavra, y->palavra, 1 + strlen(y->palavra));
  x->distancia = y->distancia;
 
  /* y <- x */
  memcpy(y->palavra, palavra, 1 + strlen(palavra));
  y->distancia = distancia;
}

unsigned int
particiona(dist **vetor, unsigned int a, unsigned int b)
{
  dist *x = vetor[b];
  unsigned int i, j;
  for (j=a, i=a-1; j<b; j++)
    if (compara_dist(vetor[j], x) <= 0) {
      i++;
      troca(vetor[i], vetor[j]);
    }

  troca(vetor[i+1], vetor[b]);

  return i + 1;
}

void
quicksort(dist **vetor, unsigned int a, unsigned int b)
{
  if (a < b) {
    unsigned int q = particiona(vetor, a, b);
    quicksort(vetor, a, q-1);
    quicksort(vetor, q+1, b);
  }
}

/* principal. */
int
main(int argc, char **argv)
{
  if (argc != 3)
    return erro("O primeiro parâmetro deve ser uma palavra e é obrigatório, \n\
o segundo parâmetro deve ser um dicionário, cada linha contendo uma palavra, e \
também é obrigatório.");

  FILE *fp = fopen(argv[2], "r");
  if (!fp)
    return erro("Erro ao abrir o dicionário: sem acesso de leitura ou inexistente.");

  char dicionario[MAX_PALAVRAS][BUFSIZ];
  unsigned int num_palavras = 0;
  while (fscanf(fp, "%s\n", dicionario[num_palavras]) != EOF)
    num_palavras++;

  /*
    associa à cada palavra do dicionário o edit distance (levenshstein distance)
    devolvendo um uma lista de pares (palavra, distancia(palavra-base, palavra)).
  */
  dist **tabela = malloc((1 + num_palavras) * sizeof(dist *));
  if (!tabela)
    return erro("Erro de alocação de memória ao construir tabela");

  unsigned int i;
  for (i = 0; i < num_palavras; i++)
    if (!(tabela[i+1] = nova_dist(dicionario[i], edit_distance(argv[1], dicionario[i]))))
      return erro("Erro ao alocar memória para uma palavra");

  quicksort(tabela, 1, num_palavras);

  /*for (i = 1; i <= num_palavras; i++)
    printf("%s [%d]\n", tabela[i]->palavra, tabela[i]->distancia);*/

  printf("Você quis dizer: %s\n", tabela[1]->palavra);

  return EXIT_SUCCESS;
}

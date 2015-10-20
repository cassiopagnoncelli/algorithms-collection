/*
  Dadas duas palavras, calcular seu edit distance.
*/
#include "edit_distance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRBUF 127

/*
  principal.
*/
int
main(int argc, char *argv[])
{
  char *p1, *p2;

  if (argc != 1 && argc != 3)
    return erro("Errou: entre sem argumentos ou com dois argumentos, que são as palavras.");

  /* ler palavras */
  if (argc == 3) {
    p1 = malloc((strlen(argv[1]) + 1) * sizeof(char));
    if (!p1) return erro("Erro ao alocar memória `p1'");
    memcpy(p1, argv[1], strlen(argv[1]) + 1);
    p2 = malloc((strlen(argv[2]) + 1) * sizeof(char));
    if (!p2) return erro("Erro ao alocar memória para `p2'");
    memcpy(p2, argv[2], strlen(argv[2]) + 1);
  } else {
    p1 = malloc(STRBUF * sizeof(char));
    if (!p1) return erro("Erro ao alocar memória para `p1'");
    p2 = malloc(STRBUF * sizeof(char));
    if (!p2) return erro("Erro ao alocar memória para `p2'");

    if (fscanf(stdin, "%s %s", p1, p2) == EOF)
      return erro("Erro ao ler palavras `p1' e `p2'.");
  }

  printf("%d\n", edit_distance(p1, p2));
  
  return EXIT_SUCCESS;
}

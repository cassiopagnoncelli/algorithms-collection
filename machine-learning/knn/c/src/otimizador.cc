/*
   Este é um otimizador para o k-NN, que encontra os melhores parâmetros
   para uma dada amostra.
*/
#include "knn_core.h"
#include <cstdio>
#include <cstring>

/* principal. */
int
main(int argc, char **argv)
{
  if (argc != 4 && argc != 5)
    return erro_msg("O otimizador requer quatro parâmetros, dentre os quais o \
último é opcional, nesta ordem:\n\
  (1) `training': caminho para o arquivo que contém a base de treinamento;\n\
  (2) `testing' : caminho para o arquivo que contém a base de teste; e\n\
  (3) `--normalizar=1' ou `--normalizar=0': indica se os dados devem ou não,\
                              respectivamente, ser normalizados.\n\
  (4) `histograma': caminho para o novo arquivo que será criado contendo o\n\
                    histograma dos resultados.");

  int normalizar; /* indica se os dados devem ou não ser normalizados. */
  if (strcmp(argv[3], "--normalizar=1") == 0)
    normalizar = 1;
  else if (strcmp(argv[3], "--normalizar=0") == 0)
    normalizar = 0;
  else
    return erro_msg("O terceiro parâmetro deve ser necessariamente\n\
  --normalizar=1   ou   --normalizar=0\n\
indicando que os dados devem ou não serem normalizados, a fim de uma melhor\n\
classificação.");

  /* abre os arquivos `training' e `testing' e carrega seus dados */
  FILE *fp_training, *fp_testing;
  if (!(fp_training = fopen(argv[1], "r")))
    return erro_msg("Impossível abrir o arquivo `training'.");

  if (!(fp_testing = fopen(argv[2], "r")))
    return erro_msg("Impossível abrir o arquivo `testing'.");

  base *training, *testing;
  if (!(training = carrega(fp_training, normalizar)))
    return erro_msg("Erro ao carregar a base de treinamento, `training'.");

  if (!(testing = carrega(fp_testing, normalizar)))
    return erro_msg("Erro ao carregar a base de teste, `testing'.");

  /* instruções para gerar o histograma */
  int gerar_histograma = (argc == 5);
  FILE *histograma = NULL;
  if (gerar_histograma) {
    histograma = fopen(argv[4], "w");
    if (!histograma)
      gerar_histograma = 0;
  }

  /* busca o valor ótimo de `k' e gera um histograma do resultado */
  int k;
  double taxa, maximo = 0.0;
  for (k = 1; k < testing->lins; k += 2) {
    taxa = knn_taxa(training, testing, k);

    if (taxa > maximo) {
      maximo = taxa;
      if (gerar_histograma)
        printf("máximo `k' local: %.5f para k=%d\n", maximo, k);
    }
    
    if (gerar_histograma)
      fprintf(histograma, "%d %.5f\n", k, taxa);
    else
      printf("%d %.5f\n", k, taxa);
  }

  if (gerar_histograma)
    fclose(histograma);

  printf("máximo `k' global: %.4f para k=%d", maximo, k-2);

  return EXIT_SUCCESS;
}

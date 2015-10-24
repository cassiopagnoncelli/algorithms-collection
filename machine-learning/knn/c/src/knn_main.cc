/*
  Implementação do classificador k-NN (k-nearest neighbor).

  Exige 4 parâmetros, dentre os quais o último é opcional, nesta ordem:
  (1) base de treinamento;
  (2) base de teste;
  (3) k;
  (4) --normalizar;
  e, portanto, deve ser chamado da seguinte forma:

    ./knn training testing k
  ou
    ./knn training testing k --normalizar

  o resultado é a taxa de acerto do classificador e a
  matriz de confusão, ambos serão impressos na saída padrão.

  --
  Cássio Jandir Pagnoncelli, cjp07 (em) inf.ufpr.br, GRR20071101
  www.inf.ufpr.br/cjp07
*/
#include "knn_core.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/* Principal. */
int
main(int argc, char **argv)
{
  /* checa os parâmetros passados */
  if (argc != 4 && argc != 5)
    return erro_msg("Chamada correta: ./knn training testing k [--normalizar]");

  int k = atoi(argv[3]);
  if (k <= 0 || k % 2 == 0)
    return erro_msg("O terceiro parâmetro, `k', será usado para distinguir \
qual a classe mais frequente dentre os k pontos com a menor distância \
e, portanto, k deve ser um inteiro ímpar positivo.");

  int normalizar = 0;
  if (argc == 5) {
    if (strcmp(argv[4], "--normalizar") == 0)
      normalizar = 1;
    else
      return erro_msg("O último parâmetro indica se os dados devem ser \
normalizados.\nA ausência de \"--normalizar\" indica que os dados devem ser \
carregados sem serem normalizados; a presença, indica que devem ser \
normalizados.");
  }

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

  /* Chamada para o classificador k-NN, que classifica os dados de `testing'
     segundo o aprendizado adquirido de `training'. Os resultados são a matriz
     de confusão e a taxa de acerto. */
  if (!knn(training, testing, atoi(argv[3])))
    return erro_msg("Erro na chamada do k-NN.");

  return EXIT_SUCCESS;
}

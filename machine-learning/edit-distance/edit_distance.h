/*
  Dadas duas palavras, calcular seu edit distance.
*/
#ifndef edit_distance_h
#define edit_distance_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* mensagem de erro. */
int erro(const char *str);

/* imprime matriz */
void imprime_matriz(unsigned int **C, unsigned int linhas, unsigned int colunas);

/* devolve min(a, min(b, c)) */
unsigned int minimo(unsigned int a, unsigned int b, unsigned int c);

/* delta: devolve 1, se os caracteres casam; 0, caso contrário. */
unsigned int delta(const char a, const char b);

/* edit distance. */
unsigned int edit_distance(const char *p1, const char *p2);

#endif /* edit_distance.h */

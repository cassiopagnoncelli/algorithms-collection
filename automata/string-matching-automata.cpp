/*
 * Computes the transition table (automaton) for the given string over the defined alphabet.
 */

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define min(x, y)   (x < y ? x : y)

#define ALPHABET_INITIAL 'a'
#define ALPHABET_FINAL   'c'

int **trans_table;
int rows;

int colchar(char c) {
  return (int) (c - ALPHABET_INITIAL);
}

bool issuffix(string x, string y) {
  if (x.length() == 0)
    return true;
  
  if (x.length() > y.length())
    return false;
  
  return x == y.substr(y.length() - x.length(), x.length());
}

void print_table() {
  int r;
  char c;

  /* Header. */
  printf("    Q |");
  for (c = ALPHABET_INITIAL; c <= ALPHABET_FINAL; c++)
    printf("  %c", c);
  printf("\n");
  printf("   ---+");
  for (c = ALPHABET_INITIAL; c <= ALPHABET_FINAL; c++)
    printf("---");
  printf("\n");

  /* Body. */
  for (r = 0; r < rows; r++) {
    printf("   %2d |", r);
    for (c = ALPHABET_INITIAL; c <= ALPHABET_FINAL; c++)
      printf(" %2d", trans_table[r][colchar(c)]);
    printf("\n");
  }
  printf("\n");
}

/* Builds the automaton. */
void comp_trans_table(string p) {
  int m = p.length();
  string Pq;
  int k, q;

  rows = m + 1;
  trans_table = (int **) malloc(rows * sizeof(int *));
  for (k = 0; k <= m; k++)
    trans_table[k] = (int *) malloc(((int)(ALPHABET_FINAL - ALPHABET_INITIAL) + 1) * sizeof(int));
  
  for (q = 0; q <= m; q++) {
    Pq = p.substr(0, q);
    for (char a = ALPHABET_INITIAL; a <= ALPHABET_FINAL; a++) {
      k = min(m + 1, q + 2);
      do { k--; } while (!issuffix(p.substr(0, k), Pq + a));
      trans_table[q][colchar(a)] = k;
    }
  }
}

/* Finite automaton matcher. */
void finite_automaton_matcher(string T, int m) {
  int n = T.length();
  int q = 0;
  for (int i = 0; i < n; i++) {
    //cout << "Go to q=" << q << " T[i]=" << T[i] << " i=" << i << endl;
    q = trans_table[q][colchar(T[i])];
    if (q == m)
      cout << "Pattern occurs with shift " << i - m << endl;
  }
}

int main(int argc, char **argv) {
  if (argc != 2 && argc != 3) {
    printf("./string-matcher pattern [string]\n");
    return 1;
  }
  
  string pattern = argv[1];
  comp_trans_table(pattern);
  print_table();
  
  if (argc == 3)
    finite_automaton_matcher(argv[2], pattern.length());
}

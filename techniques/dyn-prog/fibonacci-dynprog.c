#include <stdio.h>
#include <stdlib.h>

/* Table storing computed f(n) values. */
long long int *table;

/* Exection times. */
long long int fastfib_execs, dynpfib_execs, fib_execs;

/* Returns x^2. */
long long int sq(long long int x)
{
  return x * x;
}

/* Fast Fibonacci. */
long long int fastfib(int n)
{
  fastfib_execs++;

  if (n <= 2)
    return (n+1)/2;
  
  int half = n/2;

  return n % 2 == 0 ?
    fastfib(half) * (2 * fastfib(half + 1) - fastfib(half)) :
    sq(fastfib(half+1)) + sq(fastfib(half));
}

/* Fibonacci with dynamic programming. */
long long int dynpfib(long long int n)
{
  dynpfib_execs++;

  long long int left, right;

  if (n <= 1)
    return n;
  
  left = table[n-1] == 0 ? dynpfib(n-1) : table[n-1];
  right = table[n-2] == 0 ? dynpfib(n-2) : table[n-2];

  table[n] = left + right;

  return table[n];
}

/* Non-dynamic programming, recursive version of Fibonacci. */
long long int fib(long long int n)
{
  fib_execs++;

  return n <= 1 ? n : fib(n-1) + fib(n-2);
}

/* Dynamic programming. */
int main(int argc, char **argv)
{
  int n;
  n = 30;

  /* Table. */
  int size = 100;
  if (!(table = calloc(size, sizeof(long long int)))) return 1;

  /* Execution counts. */
  dynpfib_execs = 0;
  fastfib_execs = 0;
  fib_execs     = 0;

  dynpfib(n);
  fastfib(n);
  fib(n);

  /* Times. */
  printf("usual=%lld fast=%lld dynprog=%lld\n", fib_execs, fastfib_execs, dynpfib_execs);

  return EXIT_SUCCESS;
}

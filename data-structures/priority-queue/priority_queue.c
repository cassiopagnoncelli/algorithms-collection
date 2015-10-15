#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/* mensagem de erro. */
int
erro(const char *str)
{
  fprintf(stderr, "%s.\n", str);
  return EXIT_FAILURE;
}

/* principal. */
int
main()
{
  heap_t *heap = newheap();
  
  heap->A[1] = 3;
  heap->A[2] = 7;
  heap->A[3] = 14;
  heap->A[4] = 9;
  heap->A[5] = 19;
  heap->A[6] = 13;
  heap->A[7] = 11;
  heap->A[8] = 2;
  heap->A[9] = 8;
  heap->A[10] = 15;
  heap->A[11] = 6;
  heap->A[12] = 18;
  heap->A[13] = 10;
  heap->length = 13;
  print(heap);
  
  buildheap(heap);
  print(heap);
  
  insert(heap, 43);
  print(heap);
  
  printf("max values: ");
  while (heap->size > 0) {
    printf("%d ", extractmax(heap));
  }
  printf("\n");
  print(heap);

  return EXIT_SUCCESS;
}

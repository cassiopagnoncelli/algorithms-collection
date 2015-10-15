#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MINUS_INF -10000000

void swap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

heap_t *newheap()
{
  heap_t *heap = malloc(sizeof(heap_t));
  heap->A = malloc(MAX_SIZE * sizeof(int));
  heap->size = 0;
  heap->length = 0;
  return heap;
}

int parent(int x)
{
  return x/2;
}

int left(int x)
{
  return 2*x;
}

int right(int x)
{
  return 2*x + 1;
}

void heapify(heap_t *heap, int i)
{
  int l, r, largest;

  l = left(i);
  r = right(i);

  largest = l <= heap->size && heap->A[l] > heap->A[i] ? l : i;

  if (r <= heap->size && heap->A[r] > heap->A[largest])
    largest = r;

  if (largest != i) {
    swap(&heap->A[i], &heap->A[largest]);
    heapify(heap, largest);
  }
}

void buildheap(heap_t *heap)
{
  heap->size = heap->length;
  
  int i;
  for (i=heap->length/2; i>=1; i--)
    heapify(heap, i);
}

void print(heap_t *heap)
{
  printf("| size=%d length=%d v=", heap->size, heap->length);

  int i;
  for (i=1; i<=heap->size; i++)
    printf("%d ", heap->A[i]);
  
  for (i = heap->size+1; i <= heap->length; i++)
    printf(":%d ", heap->A[i]);
  
  printf("\n");
}

int maximum(heap_t *heap)
{
  return heap->A[1];
}

int extractmax(heap_t *heap)
{
  if (heap->size < 1) {
    fprintf(stderr, "Heap underflow.\n");
    exit(1);
  }

  int ret = heap->A[1];
  
  heap->A[1] = heap->A[heap->size];
  heap->size--;
  heapify(heap, 1);
  
  return ret;
}

void inckey(heap_t *heap, int i, int key)
{
  if (key < heap->A[i]) {
    fprintf(stderr, "New key is smaller than current key.\n");
    exit(1);
  }

  heap->A[i] = key;
  
  while (i > 1 && heap->A[parent(i)] < heap->A[i]) {
    swap(&heap->A[i], &heap->A[parent(i)]);
    i = parent(i);
  }
}

void insert(heap_t *heap, int key)
{
  heap->size++;
  heap->A[heap->size] = MINUS_INF;
  inckey(heap, heap->size, key);
}

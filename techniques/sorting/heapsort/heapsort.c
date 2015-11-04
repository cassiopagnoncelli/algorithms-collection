#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

/* Heap data structure. */
typedef struct {
  int *v;
  int length;
  int heapsize;
} heap_t;

heap_t *createheap(int size)
{
  heap_t *h = malloc(sizeof(heap_t));
  if (!h) return NULL;

  h->v = malloc((size+1) * sizeof(int));
  if (!h->v) return NULL;

  h->length = size;
  h->heapsize = 0;

  return h;
}

void destroyheap(heap_t *h)
{
  if (!h) return;
  if (h->v) free(h->v);
  free(h);
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

void printheap(heap_t *h)
{
  int i;
  printf("| ");
  for (i = 1; i <= h->length; i++)
    printf("%d ", h->v[i]);
  printf("\n");
}

void max_heapify(heap_t *heap, int i)
{
  int l, r, largest;

  l = left(i);
  r = right(i);

  if (l <= heap->heapsize && heap->v[l] > heap->v[i])
    largest = l;
  else
    largest = i;

  if (r <= heap->heapsize && heap->v[r] > heap->v[largest])
    largest = r;

  if (largest != i) {
    swap(&heap->v[i], &heap->v[largest]);
    max_heapify(heap, largest);
  }
}

void build_maxheap(heap_t *heap)
{
  int i;

  heap->heapsize = heap->length;
  for (i=heap->length/2; i>=1; i--)
    max_heapify(heap, i);
}

void heapsort(heap_t *heap)
{
  build_maxheap(heap);

  int i;
  for (i=heap->length; i>=2; i--) {
    swap(&heap->v[1], &heap->v[i]);
    heap->heapsize--;
    max_heapify(heap, 1);
  }
}

int main(int argc, char **argv)
{
  heap_t *heap = createheap(15);
  heap->v[0] = 0;
  heap->v[1] = 10;
  heap->v[2] = 13;
  heap->v[3] = 7;
  heap->v[4] = 16;
  heap->v[5] = 3;
  heap->v[6] = 23;
  heap->v[7] = 19;
  heap->v[8] = 14;
  heap->v[9] = 12;
  heap->v[10] = 9;
  heap->v[11] = 6;
  heap->v[12] = 8;
  heap->v[13] = 1;
  heap->v[14] = 15;
  heap->v[15] = 2;
  heap->length = 15;
  heap->heapsize = 15;

  heapsort(heap);

  printheap(heap);

  return EXIT_SUCCESS;
}

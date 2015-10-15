#ifndef heap_h
#define heap_h

void swap(int *a, int *b);

typedef struct {
  int *A;
  int size;
  int length;
} heap_t;

heap_t *newheap();

int parent(int x);
int left(int x);
int right(int x);

void heapify(heap_t *heap, int i);
void buildheap(heap_t *heap);

void print(heap_t *heap);

int maximum(heap_t *heap);
int extractmax(heap_t *heap);
void inckey(heap_t *heap, int i, int key);
void insert(heap_t *heap, int key);

#endif /* heap.h */

#include <stdio.h>
#include <stdlib.h>

/* Hash table class. */
typedef struct hash_tt
{
  int *v;
  int size;
} hash_t;

int construct(hash_t *h)
{
  if (!h)
    return 0;

  h->size = 100;
  h->v = (int *) malloc(h->size * sizeof(int));
  if (!h->v)
    return 0;

  return 1;
}

int destruct(hash_t *h)
{
  if (!h || !h->v)
    return 0;

  free(h->v);

  return 1;
}

int insert(hash_t *h, int value)
{
  int key;

  if (!h)
    return 0;

  key = (value * 101) % h->size;
  h->v[key] = value;

  return 1;
}

int delete(hash_t *h, int value)
{
  int key;

  if (!h)
    return 0;

  key = (value * 101) % h->size;
  h->v[key] = 0;

  return 1;
}

int search(hash_t *h, int value)
{
  int key;

  if (!h)
    return -1;

  key = (value * 101) % h->size;

  return h->v[key] == 0 ? -1 : key;
}

int main(int argc, char **argv)
{
  hash_t hash;
  int x;

  if (!construct(&hash)) return 1;

  if (!insert(&hash, 10)) return 2;
  if (!insert(&hash, 3)) return 3;
  if (!insert(&hash, 19)) return 4;
  if (!insert(&hash, 23)) return 5;
  if (!insert(&hash, 42)) return 6;

  x = search(&hash, 3);
  printf("3 at %d\n", x);

  x = search(&hash, 11);
  printf("11 at %d\n", x);

  if (!delete(&hash, 3)) return 7;

  x = search(&hash, 3);
  printf("after removal... 3 at %d\n", x);

  if (!destruct(&hash)) return 8;
  
  return EXIT_SUCCESS;
}

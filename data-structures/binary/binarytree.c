#include <stdio.h>
#include <stdlib.h>

/* Tree structure. */
struct tree_tt
{
  int element;
  struct tree_tt *leftchild;
  struct tree_tt *rightchild;
};

typedef struct tree_tt tree_t;

/*
  There are three ways to traverse a tree: in pre-order, in-order, or
  post-order.
*/
enum order_e { PREORDER, INORDER, POSTORDER };

/* Traverse the tree printing its elements in the given order. */
void printtree(tree_t *tree, enum order_e order)
{
  if (!tree) {
    printf("()");
    return;
  }

  switch (order) {
  case PREORDER:
    if (!tree->leftchild && !tree->rightchild)
      printf("(%d)", tree->element);
    else {
      printf("(%d,", tree->element);
      printtree(tree->leftchild, PREORDER);
      printf(",");
      printtree(tree->rightchild, PREORDER);
      printf(")");
    }
    break;
  case INORDER:
    if (!tree->leftchild && !tree->rightchild)
      printf("(%d)", tree->element);
    else {
      printf("(");
      printtree(tree->leftchild, PREORDER);
      printf(",%d,", tree->element);
      printtree(tree->rightchild, PREORDER);
      printf(")");
    }
    break;
  case POSTORDER:
    if (!tree->leftchild && !tree->rightchild)
      printf("(%d)", tree->element);
    else {
      printf("(");
      printtree(tree->leftchild, PREORDER);
      printf(",");
      printtree(tree->rightchild, PREORDER);
      printf("%d)", tree->element);
    }
    break;
  default:
    printf("What?\n");
    break;
  }
}

/* Initialize tree. */
int construct(tree_t *tree)
{
  if (!tree)
    return 0;

  tree->leftchild = NULL;
  tree->rightchild = NULL;

  return 1;
}

/* Removes left/right sub-trees and returns a pointer to `tree'. */
tree_t *destruct(tree_t *tree)
{
  if (!tree)
    return NULL;

  if (tree->leftchild) free(destruct(tree->leftchild));
  if (tree->rightchild) free(destruct(tree->rightchild));
  
  return tree;
}

/* Inserts `x' into the given tree. */
int insert(tree_t *tree, int x)
{
  /* Check tree. */
  if (!tree)
    return 0;
  
  /* Check duplicate. */
  if (x == tree->element) {
    printf("%d is already in the tree.\n", x);
    return 0;
  }

  /* Insert within left/right sub-tree. */
  if (x < tree->element) {
    /* Insert at left sub-tree if a left sub-tree already exists. */
    if (tree->leftchild)
      return insert(tree->leftchild, x);
    
    /* Create a new left sub-tree insert `x' at its root. */
    tree->leftchild = malloc(sizeof(tree_t));
    if (!tree->leftchild)
      return 0;

    tree->leftchild->element = x;
  } else {
    if (tree->rightchild)
      return insert(tree->rightchild, x);

    /* Create a new left sub-tree insert `x' at its root. */
    tree->rightchild = malloc(sizeof(tree_t));
    if (!tree->rightchild)
      return 0;

    tree->rightchild->element = x;
  }

  return 1;
}

/* Main program. */
int main(int argc, char **argv)
{
  tree_t tree;
  int i;

  if (argc < 2) return 1;

  if (!construct(&tree)) return 2;

  tree.element = atoi(argv[1]);

  for (i=2; i<argc; i++)
    if (!insert(&tree, atoi(argv[i])))
      printf("Something went wrong.\n");

  printtree(&tree, PREORDER);
  printf("\n");

  destruct(&tree);

  return EXIT_SUCCESS;
}

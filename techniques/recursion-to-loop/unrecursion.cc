/*
  Read
  http://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
  to see why it works.
*/
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <cassert>

using namespace std;

typedef struct funcall_tt {
  /* Parameters. */
  int n;

  /* Local variables. */
  long long int ret;
  long long int a;
  long long int b;

  /* Sliced part of the function. */
  int stage;
} funcall_t;

/* Ctor. */
funcall_t *funcall_new(int n)
{
  funcall_t *f = (funcall_t *) malloc(sizeof(funcall_t));
  if (!f)
    return NULL;

  f->n = n;
  f->ret = 0;
  f->a = 0;
  f->b = 0;
  f->stage = 0;

  return f;
}

void printfuncall(funcall_t *fc)
{
  printf("[n=%d,stage=%d,ret=%lld,a=%lld,b=%lld]",
         fc->n,
         fc->stage,
         fc->ret,
         fc->a,
         fc->b);
}

void printstack(stack<funcall_t *> s)
{
  return;        /* print nothing. */

  stack<funcall_t *> tmp;

  while (!s.empty()) {
    tmp.push(s.top());
    s.pop();
  }

  printf("| ");
  while (!tmp.empty()) {
    printfuncall(tmp.top());
    printf(" ");
    s.push(tmp.top());
    tmp.pop();
  }

  printf("\n");
}

long long int nonrecursivef(int x)
{
  funcall_t *cur;                        /* Current function call snapshot. */
  long long int r = 0;                                    /* Return result. */

  /* Stack frame. */
  stack<funcall_t *> stackframe;
  
  /* Call to f(x). */
  stackframe.push(funcall_new(x));

  /* Simulates stack frame behaviour. */
  printstack(stackframe);
  while (!stackframe.empty())
  {
    cur = stackframe.top();
    stackframe.pop();

    switch(cur->stage) {
    case 0:
      if (cur->n <= 1)
        r = cur->n;
      else {
        cur->stage++;
        stackframe.push(cur);

        stackframe.push(funcall_new(cur->n - 1));           /* call f(n-1). */
      }
      break;
    case 1:
      cur->stage++;
      stackframe.push(cur);

      cur->a = r;                                            /* a = f(n-1); */
      stackframe.push(funcall_new(cur->n - 2));             /* call f(n-2). */
      break;
    case 2:
      cur->b = r;                                            /* b = f(n-2); */
      cur->ret = cur->a + cur->b;                           /* ret = a + b; */
      r = cur->ret;                                            /* return r; */
      break;
    default:
      break;
    }

    printstack(stackframe);
  }

  return r;
}

long long int recursivef(int n)
{
  long long int ret;
  long long int a;
  long long int b;

  if (n <= 1) {
    ret = n;
  } else {
    a = recursivef(n-1);
    b = recursivef(n-2);
    ret = a + b;
  }

  return ret;
}

int main(int argc, char **argv)
{
  int i;
  for (i=0; i<20; i++)
    assert(nonrecursivef(i) == recursivef(i));
  
  return EXIT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                             *
 * Dijkstra's algorithm in C.                                  *
 *                                                             *
 * By MHE, 4th Mar 2003.                                       *
 *                                                             *
 * If you don't know C but know some Java, you should be able  *
 * to read this by making some educated guesses.               *
 *                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <limits.h>
#include <assert.h>

/* C lacks some very basic types, but we can easily define them. */

typedef enum {false, true} bool; /* The order is rather important to
                                    get the boolean values right. */
typedef char *string;

/* 
  We take the maximum unsigned integer (as defined in the standard
  header value.h) as the value of infinity. So this shouldn't be the
  number of vertices of any path in our graph, because the algorthm
  won't work. (But I haven't been careful enough to include assertions
  to make sure that inputs that violate this assumptions are detected.
  If it is violated, only God knows what is going to happen when you
  run the program. This is definitely not good practice, but, because
  I am not going to sell this program, I just ask the users not to
  attempt bad inputs at home.)

  We define a type of values for weights, which can be changed (to
  e.g. floats) if required. But, as discussed in the lectures, the
  algorithm works for nonnegative values only.
*/

#define oo UINT_MAX /* infinity is represented as the maximum unsigned int. */

typedef unsigned int value;

/* 
   In order to avoid complications with IO, we include the graph in
   the program directly. Of course, one wouldn't do that in practice.
*/


/* Firstly, the type of vertices for our particular graph (which was
   given as an example in the lectures). The (non)vertex `nonexistent'
   is used in order to indicate that a vertex hasn't got a predecessor
   in the path under consideration. See below. */

typedef enum { HNL, SFO, LAX, ORD, DFW, LGA, PVD, MIA, nonexistent} vertex; 

/* If you modify the above, in order to consider a different graph,
   then you also have to modify the following. */

const vertex first_vertex = HNL;
const vertex last_vertex = MIA;

#define no_vertices 8 /* NB. This has to be the same as the number
                         (last_vertex + 1), which unfortunately
                         doesn't compile... */

/* Now a dictionary for output purposes. The order has to match the
   above, so that, for example, name[SFO]="SFO". */

string name[] = {"HNL","SFO","LAX","ORD","DFW","LGA", "PVD", "MIA"};

/* Now the weight matrix of our graph (as given in the
   lectures). Because the graph is undirected, the matrix is
   symmetric. But our algorithm is supposed to work for directed
   graphs as well (and even for disconnected ones - see below). */

value weight[no_vertices][no_vertices] =
  {
   /*  HNL    SFO    LAX    ORD    DFW    LGA   PVD    MIA  */
    {    0,   oo,  2555,    oo,    oo,    oo,    oo,    oo}, /* HNL */
    {   oo,    0,   337,  1843,    oo,    oo,    oo,    oo}, /* SFO */
    { 2555,  337,     0,  1743,  1233,    oo,    oo,    oo}, /* LAX */
    {   oo, 1843,  1743,     0,   802,    oo,   849,    oo}, /* ORD */ 
    {   oo,   oo,  1233,   802,     0,  1387,    oo,  1120}, /* DFW */
    {   oo,   oo,    oo,    oo,  1387,     0,   142,  1099}, /* LGA */
    {   oo,   oo,    oo,   849,    oo,   142,     0,  1205}, /* PVD */
    {   oo,   oo,    oo,    oo,  1120,  1099,   1205,    0}  /* MIA */
  };


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *     
 * The implementation of Dijkstra's algorithm starts here. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* We first declare the array `D' of overestimates, the array `tight'
   which records which of those estimates are actually tight, and the
   array `predecessor'. The last has the property that predecessor[z]
   is the last vertex visited on the way from the start node to z. */

value D[no_vertices]; 
bool tight[no_vertices];
vertex predecessor[no_vertices];

/* 
  We begin with the following auxiliary function, which should be
  called only when we know for sure that there is at least one node u
  with tight[u] false. Otherwise, the program aborts; this happens
  when the assertion below fails.
 */

vertex minimal_nontight() {

  vertex j, u;

  for (j = first_vertex; j <= last_vertex; j++) 
     if (!tight[j]) 
        break;

  assert(j <= last_vertex); 

  u = j; 

 /* Now u is the first vertex with nontight estimate, but not
     necessarily the one with minimal estimate, so we aren't done
     yet. */

 
  for (j++; j <= last_vertex; j++)
     if (!tight[j]  &&  D[j] < D[u])
          u = j;

  /* Having checked all vertices, we now know that u has the required
     minimality property. */ 

  return u;
}

/* 
   The following definition assumes that the graph is directed in
   general, which means that it would be wrong to have weight[z][u]
   instead. The intended meaning is that the vertex u has the vertex z
   as one of its successors. Recall that such a vertex z was
   called a neighbour of the vertex u, but this latter terminology is
   best reserved for undirected graphs. Notice that the example given
   above happens to be undirected. But, as remarked above, this
   program is intended to work for directed graphs as well. 
 */

bool successor(vertex u, vertex z) {
  return (weight[u][z] != oo  &&  u != z);
}


/* 
  We finally arrive at the main algorithm. This is the same as given
  above, now written in C, with the computation of the actual
  paths included. The computation of paths is achieved via the use of
  the array `predecessor' declared above. Strictly speaking,
  Dijkstra's algorithm only records what is needed in order to recover
  the path. The actual computation of the path is performed by the
  algorithm that follows it.
 */

void dijkstra(vertex s) {

  vertex z, u;
  int i;

  D[s] = 0;

  for (z = first_vertex; z <= last_vertex; z++) {

    if (z != s)
      D[z] = oo;

    tight[z] = false;
    predecessor[z] = nonexistent;
  }

  for (i = 0; i < no_vertices; i++) {

    u = minimal_nontight();
    tight[u] = true;

    /* In a disconnected graph, D[u] can be oo. But then we just move
       on to the next iteration of the loop. (Can you see why?) */

    if (D[u] == oo)
      continue; /* to next iteration ofthe for loop */

    for (z = first_vertex; z <= last_vertex; z++)
      if (successor(u,z) && !tight[z] && D[u] + weight[u][z] < D[z]) {
        D[z] = D[u] + weight[u][z]; /* Shortcut found. */
        predecessor[z] = u;
      }
  }
}

/* The conditions (successor(u,z) && !tight[z]) can be omitted from
   the above algorithm without changing its correctness. But I think
   that the algorithm is clearer with the conditions included, because
   it makes sense to attempt to tighten the estimate for a vertex only
   if the vertex is not known to be tight and if the vertex is a
   successor of the vertex under consideration. Otherwise, the
   condition (D[u] + weight[u][z] < D[z]) will fail anyway. However,
   in practice, it may be more efficient to just remove the conditions
   and only perform the test (D[u] + weight[u][z] < D[z]). */

/* We can now use Dijkstra's algorithm to compute the shortest path
   between two given vertices. It is easy to go from the end of the
   path to the beginning. 

   To reverse the situation, we use a stack. Therefore we digress
   slightly to implement stacks (of vertices). In practice, one is
   likely to use a standard library instead, but, for teaching
   purposes, I prefer this program to be selfcontained. */

#define stack_limit 10000 /* Arbitrary choice. Has to be big enough to
                             accomodate the largest path. */

vertex stack[stack_limit];
unsigned int sp = 0; /* Stack pointer. */

void push(vertex u) {
  assert(sp < stack_limit); /* We abort if the limit is exceeded. This
                               will happen if a path with more
                               vertices than stack_limit is found. */
  stack[sp] = u;
  sp++;
}

bool stack_empty() {
  return (sp == 0);
}

vertex pop() {
  assert(!stack_empty()); /* We abort if the stack is empty. This will
                             happen if this program has a bug. */
  sp--;
  return stack[sp];
}

/* End of stack digression and back to printing paths. */

void print_shortest_path(vertex origin, vertex destination) {

  vertex v;

  assert(origin != nonexistent  &&  destination != nonexistent);

  dijkstra(origin);

  printf("The shortest path from %s to %s is:\n\n",
         name[origin], name[destination]);

  for (v = destination; v != origin; v = predecessor[v])
    if (v == nonexistent) {
      printf("nonexistent (because the graph is disconnected).\n");
      return;
    }
    else
      push(v);

  push(origin); 

  while (!stack_empty()) 
    printf(" %s",name[pop()]);

  printf(".\n\n");
}


/* We now run an example. */

int main() {

  print_shortest_path(SFO,MIA);

  return 0; /* Return gracefully to the caller of the program
               (provided the assertions above haven't failed). */
}

/* End of program. */


#include <stdio.h>
#include <limits.h>
#include <assert.h>

typedef enum {false, true} bool;

typedef char *string;

#define oo UINT_MAX

typedef unsigned int value;

typedef enum { HNL, SFO, LAX, ORD, DFW, LGA, PVD, MIA, nonexistent} vertex; 

const vertex first_vertex = HNL;
const vertex last_vertex = MIA;

#define no_vertices 8 /* NB. This has to be the same as the number
                         (last_vertex + 1), which unfortunately
                         doesn't compile... */

string name[] = {"HNL","SFO","LAX","ORD","DFW","LGA", "PVD", "MIA"};

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

value D[no_vertices]; 
bool tight[no_vertices];
vertex predecessor[no_vertices];

vertex minimal_nontight() {

  vertex j, u;

  for (j = first_vertex; j <= last_vertex; j++) 
     if (!tight[j]) 
        break;

  assert(j <= last_vertex); 

  u = j; 

  for (j++; j <= last_vertex; j++)
     if (!tight[j]  &&  D[j] < D[u])
          u = j;
  
  return u;
}
bool successor(vertex u, vertex z) {
  return (weight[u][z] != oo  &&  u != z);
}

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

    if (D[u] == oo)
      continue;

    for (z = first_vertex; z <= last_vertex; z++)
      if (successor(u,z) && !tight[z] && D[u] + weight[u][z] < D[z]) {
        D[z] = D[u] + weight[u][z];
        predecessor[z] = u;
      }
  }
}

#define stack_limit 10000

vertex stack[stack_limit];
unsigned int sp = 0; /* Stack pointer. */

void push(vertex u) {
  assert(sp < stack_limit);
  stack[sp] = u;
  sp++;
}

bool stack_empty() {
  return (sp == 0);
}

vertex pop() {
  assert(!stack_empty()); 
  sp--;
  return stack[sp];
}

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

int main()
{
  print_shortest_path(SFO,MIA);
  return 0;
}


#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define INDEX(i,j,n) (i * n + j)

Graph createGraph(int maxSize) {
  Graph g;
  g.matrix = (int*) malloc(sizeof(int) * maxSize * maxSize);
  memset(g.matrix, 0, sizeof(int) * maxSize * maxSize);
  g.maxSize = maxSize;
  return g;
}

void addEdge(Graph g, int v1, int v2) {
  g.matrix[INDEX(v1,v2,g.maxSize)] = 1;
  g.matrix[INDEX(v2,v1,g.maxSize)] = 1;
}

int isAdjacent(Graph g, int v1, int v2) {
  return g.matrix[INDEX(v1,v2,g.maxSize)];
}

int getAdjacentVertices(Graph g, int v, int *output) {
  int i, n;
  n = 0;
  for (i = 0; i < g.maxSize; i ++)
    if (isAdjacent(g, v, i))
      output[n++] = i;
  return n;
}

void dropGraph(Graph g) {
  free(g.matrix);
}

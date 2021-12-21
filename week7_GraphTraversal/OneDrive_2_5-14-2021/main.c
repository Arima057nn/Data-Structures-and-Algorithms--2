
#include "graph.h"

void printNode(int key)
{
  printf("%d\n", key);
}

int main()
{
  Dllist out;
  int i, n, output[100];
  Graph g = createGraph(100);
  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 3, 4);
  addEdge(g, 0, 5);
  addEdge(g, 5, 6);
  out = getAdjacentVertices(g, 0);
  while (out != NULL)
  {
    printf("%d\t\n", jval_i(out->val));
    out = out->flink;
  }
  
  
  BFS(g, 0, printNode);
  return 0;
}

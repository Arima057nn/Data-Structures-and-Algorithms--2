#include <stdio.h>
#include "graph.h"

void printNode(int key) {
  printf("%d\n", key);
}

int main() {
  Graph g = createGraph();
  addVertex(g, 0, "Dung");
  addVertex(g, 1, "Bao");
  addVertex(g, 2, "Duc");
  addVertex(g, 3, "Cong");
  addVertex(g, 4, "Hai");
  addVertex(g, 5, "Tuyen");
  addVertex(g, 6, "Tuan");
 
  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 3, 4);
  addEdge(g, 0, 5);
  addEdge(g, 5, 6);
  //addEdge(g, 4, 1);  
  DFS(g, 0, -1, printNode);
  printf("\n%s\n",getVertexName(g,1));
  printf("%d\n",getVertexId(g,"Dung"));
  if (isDAG(g))
    printf("This is a DAG!\n");
  else
    printf("This is not a DAG!\n");
  return 0;
}

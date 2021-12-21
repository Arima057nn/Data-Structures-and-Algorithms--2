#include "directedGraph.h"

void printNode(int key) {
  printf("%d\n", key);
}

Dllist topological_sort(Graph g, int* out, int* n) {
    Dllist node, queue;
    JRB vertex;
    queue = new_dllist();
    *n = 0;
    int o[1000];
    
    int* indegree = in_deg_arr(g);
    jrb_traverse(vertex, g.vertices) {
        if(indegree[jval_i(vertex->key)] == 0)
            dll_append(queue, vertex->key);
    }
    while ( !dll_empty(queue) )
    {
      node = dll_first(queue);
      int v = jval_i(node->val);
      dll_delete_node(node);
      out[(*n)++] = v;
      int n = out_deg(g, v, o);
      for(int i = 0; i < n; ++i) {
          indegree[out[i]]--;
          if(indegree[out[i]] == 0)
            dll_append(queue, new_jval_i(out[i]));
      }
   }
}


int main() {
  Graph g = createGraph();
  int output[100], n;

  addVertex(g, 0, "CS102");
  addVertex(g, 1, "CS140");
  addVertex(g, 2, "CS160");
  addVertex(g, 3, "CS302");
  addVertex(g, 4, "CS311");
  addVertex(g, 5, "MATH300");
  
  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 3);
  addEdge(g, 5, 4);
  addEdge(g, 3, 4);
  if (isDAG(g))
    printf("This is a DAG!\n");
  else
    printf("This is not a DAG!\n");

  

  if (isDAG(g))
    printf("This is a DAG!\n");
  else
    printf("This is not a DAG!\n");
  topological_sort(g, output, &n);

  for (int i=0; i<n; i++)
        printf("%s\n", getVertexName(g, output[i]));
  return 0;
}

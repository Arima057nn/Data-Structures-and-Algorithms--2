#include <stdlib.h>
#include "graph_jrb.h"
Graph createGraph(){
    Graph graph = make_jrb();
    return graph;
}
void addEdge(Graph graph,int v1,int v2){
    JRB node,tree;
    node = jrb_find_int(graph,v1);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph,v1,new_jval_v(tree));
        jrb_insert_int(tree,v2,new_jval_i(1));
    }else{
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    node = jrb_find_int(graph,v2);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph,v2,new_jval_v(tree));
        jrb_insert_int(tree,v1,new_jval_i(1));
    }else{
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}
int getAdjacentVertices(Graph graph,int vertex,int *output){
    JRB node = jrb_find_int(graph,vertex);
    JRB tree = (JRB)jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree){
        output[total++] = jval_i(node->key);
    }
    return total;
}
void dropGraph(Graph graph){
    JRB node;
    jrb_traverse(node,graph){
        jrb_free_tree(jval_v(node->val));
    }
    jrb_free_tree(graph);
}


int isAdjacent(Graph g, int v1, int v2) {
  JRB node;

  if ((node = jrb_find_int(g, v1)) != NULL) {
    if (jrb_find_int((JRB)(jval_v(node->val)), v2) != NULL)
      return 1;
    else return 0;
  } else return 0;
}

// Dllist getAdjacentVertices(Graph g, int v) {
//   int n = 0;
//   JRB node, l, i;
//   Dllist output = new_dllist();
 
//   if ((node = jrb_find_int(g, v)) == NULL)
//     return output;

//   l = (JRB)jval_v(node->val);
//   jrb_traverse(i, l) {
//     dll_append(output, i->key);
//   }
//   return output;
// }

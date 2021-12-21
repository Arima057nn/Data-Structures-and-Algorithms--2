#ifndef __GRAPH_JRB_H__
#include "jrb.h"
typedef JRB Graph;
Graph createGraph();
void addEdge(Graph graph,int v1,int v2);
int getAdjacentVertices(Graph graph,int vertex,int *output);
//return the Number of adjacent vertices.
void dropGraph(Graph graph);
#endif

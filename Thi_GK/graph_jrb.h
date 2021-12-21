#ifndef __GRAPH_JRB_H__
#include "jrb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef JRB Graph;
Graph createGraph();
void addEdge(Graph graph,char* v1,char* v2,int *vertex,Jval list[][2]);
int getAdjacentVertices(Graph graph,char* vertex,char** output);
//return the Number of adjacent vertices.
void dropGraph(Graph graph);
int isvisited(Jval j,Jval visit ed[][2],int vertex);
void visit(Jval j,Jval visited[][2],int vertex);

#endif
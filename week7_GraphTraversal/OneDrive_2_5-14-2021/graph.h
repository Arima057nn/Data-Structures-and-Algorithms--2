#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "dllist.h"

typedef JRB Graph;

Graph createGraph(int maxSize);
void addEdge(Graph g, int v1, int v2);
int isAdjacent(Graph g, int v1, int v2);
//int getAdjacentVertices(Graph g, int v, int *output);
Dllist getAdjacentVertices(Graph g, int v);
void dropGraph(Graph g);

void BFS(Graph g, int v, void (*f)(int key)); 

#endif
  

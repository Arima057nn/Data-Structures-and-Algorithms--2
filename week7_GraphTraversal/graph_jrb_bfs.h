#ifndef __GRAPH_JRB_H__
#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
#define MAX 100
typedef JRB Graph;
Graph createGraph();
void addEdge(Graph graph,int v1,int v2);
int getAdjacentVertices(Graph graph,int vertex,int *output);
//return the Number of adjacent vertices.
void dropGraph(Graph graph);
Dllist queue_initialize();
void enqueue(Dllist queue,int v);
int isempty(Dllist queue);
int dequeue(Dllist queue);
void printfVertex(int v);
void BFS(Graph graph,int start, int stop, void (*func)(int));
#endif

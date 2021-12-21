#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "jrb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dllist.h"

typedef struct
{
  JRB vertices;
  JRB edges;
} Graph;

Graph createGraph();
void addVertex(Graph g, int id, char *name); //Them mot dinh
void addEdge(Graph g, int v1, int v2);       // Them mot canh

char *getVertexName(Graph g, int id); // tim kiem ten theo id
int getVertexId(Graph g, char *name); // tim kiem id theo ten

int hasEdge(Graph g, int v1, int v2); // Co noi  voi nhau hay khong

Dllist incomingVertices(Graph g, int v);
Dllist outgoingVertices(Graph g, int v);

void dropGraph(Graph g); //Giai phong bo nho

void BFS(Graph g, int source, int dest, void (*f)(int key));
void DFS(Graph g, int source, int dest, void (*f)(int key));
int isDAG(Graph g);

#endif

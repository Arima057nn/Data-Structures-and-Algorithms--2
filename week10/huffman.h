#ifndef __GRAPH_JRB_H__
#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
#include "string.h"

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;
Graph createGraph();

void addVertex(Graph g, int id, char *name);
char *getVertexName(Graph g, int id);

void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2); // return INFINITIVE_VALUE if no edge between v1 and v2 int indegree(Graph graph, int v, int *output);

int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);

void dropGraph(Graph graph);

typedef struct
{
    Graph graph;
    JRB root;
} HuffmanTree;

HuffmanTree makeHuffman(char *buffer, int size);

typedef struct
{
    int size;
    char bits[20]; //MAXINUM 20 BITS, IT IS SAFE ENOUGH
} Coding;

typedef struct
{
    int size;
    int *nodes;
} HuffmanTreeArray;



#endif

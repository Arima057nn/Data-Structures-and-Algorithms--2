#include "library.h"

void pruferCode(Graph g){
    
}

int main()
{
    Graph g = createGraph();
    int A[100], i;
    addVertex(g, 0, "n");
    addVertex(g, 1, "n");
    addVertex(g, 2, "n");
    addVertex(g, 3, "n");
    addVertex(g, 4, "n");
    addVertex(g, 5, "n");
    addVertex(g, 6, "n");
    addVertex(g, 7, "n");
    addVertex(g, 8, "n");
    addVertex(g, 9, "n");
    addEdge(g, 0, 2, 1);
    addEdge(g, 0, 3, 1);
    addEdge(g, 2, 4, 1);
    addEdge(g, 2, 6, 1);
    addEdge(g, 2, 9, 1);
    addEdge(g, 6, 1, 1);
    addEdge(g, 6, 5, 1);
    addEdge(g, 9, 7, 1);
    addEdge(g, 9, 8, 1);
    return 0;
}

//gcc -I ../Libfdr/ -o GK GK.c graph_jrb.c ../Libfdr/libfdr.a
// ./GK
#include <stdio.h>
#include "graph_jrb.h"
#define sizemax 100
int main(){
    int i,n,output[sizemax];
    Graph g = createGraph();
    addEdge(g,0,1);
    addEdge(g,0,2);
    addEdge(g,1,2);
    addEdge(g,1,3);
    n = getAdjacentVertices(g,1,output);
    if(n==0) printf("No adjacent vertices of node 1\n");
    else{
        printf("Adjacent vertices of node 1: ");
        for(i=0;i<n;i++) printf("%5d",output[i]);
    }
    dropGraph(g);
    printf("\n\n");
    return 0;
}

// gcc -I Library/Libfdr/ -o week7/bfs_traverse week7/bfs_traverse.c week7/graph_jrb_bfs.c Library/Libfdr/libfdr.a 

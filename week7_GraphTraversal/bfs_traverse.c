#include "graph_jrb_bfs.h"
int main(){
    Graph g = createGraph();
    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,1,3);
    addEdge(g,2,3);
    addEdge(g,2,4);
    addEdge(g,4,5);
    addEdge(g,5,6);
    addEdge(g,6,1);
    printf("\nBFS: start from node 1 to 6:");
    BFS(g,1,6,printfVertex);
    printf("\nBFS: start from node 1 to all:");
    BFS(g,1,-1,printfVertex);
    printf("\n");
    return 0;
}

//  gcc -I Library/Libfdr/ -o week7/bfs_traverse week7/bfs_traverse.c week7/graph_jrb_bfs.c Library/Libfdr/libfdr.a 

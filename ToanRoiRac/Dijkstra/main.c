#include "library.h"

void readFileTXT(FILE *ptr, FILE *fptr, Graph g)
{
    int vertex, edge, a, b;
    double c;
    fprintf(fptr, "graph G{\n");
    fscanf(ptr, "%d%*c", &vertex);
    fscanf(ptr, "%d%*c", &edge);
    while (fscanf(ptr, "%d%d%lf%*c", &a, &b, &c) == 3)
    {
        addVertex(g, a, "n");
        addVertex(g, b, "n");
        addEdge(g, a, b, c);
        fprintf(fptr,"\t%d -- %d;\n",a,b);
    }
    fprintf(fptr, "\n}\n");
    fclose(ptr);
    fclose(fptr);
}
int main(int argc, char *argv[])
{
    Graph g = createGraph();
    FILE *fptr = fopen("graph.dot", "w");
    FILE *ptr = fopen(argv[1], "r");
    readFileTXT(ptr, fptr, g);
    //BFS(g, 1, -1, printfVertex);
    printf("\n");
    return 0;
}

//gcc -I ../Libfdr/ -o GK GK.c graph_jrb.c ../Libfdr/libfdr.a
// ./GK
#include "weighted_Graph.h"

int main()
{
    int i, length, path[100], s, t;
    double w;
    Graph g = createGraph();
    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addEdge(g, 0, 1, 1);
    addEdge(g, 1, 2, 3);
    addEdge(g, 2, 0, 3);
    addEdge(g, 1, 3, 1);
    addEdge(g, 2, 3, 1);
    s = 2;
    t = 3;
    w = shortestPath(g, s, t, path, &length);
    if (w == INFINITIVE_VALUE)
    {
        printf("No path from %s to %s\n", getVertexName(g, s), getVertexName(g, t));
    }
    else
    {
        printf("Path from %s to %s (with total distance %f)\n", getVertexName(g, s), getVertexName(g, t), w);
        for (i = 0; i < length; i++)
            printf(" => %s", getVertexName(g, path[i]));
    }

    dropGraph(g);
    return 0;
}
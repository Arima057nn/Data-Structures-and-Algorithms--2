#include "library.h"

void InCase2(Graph graph)
{
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.edges)
    {
        printf("%d %s\n", jval_i(node1->key), getVertexName(graph, jval_i(node1->key)));
    }
}

int readCommand(int argc, char *agrv[])
{
    if (strcmp(agrv[0], "./p") != 0)
    {
        printf("Ten file bi sai\n");
        exit(0);
    }
    if (argc == 3)
    {
        return 2;
    }
    if (argc == 4)
    {
        return 5;
    }
    if (argc == 5)
    {
        if (strcmp(agrv[1], "-w") == 0)
            return 3;
        if (strcmp(agrv[1], "-p") == 0)
            return 4;
        if (strcmp(agrv[1], "-s") == 0)
            return 6;
    }
}

int main(int argc, char *argv[])
{
    FILE *ptr;
    Dllist p, list;
    Graph g = createGraph();
    int choose, vertex, edge;
    int i = 0, a, b;
    double c;
    char s[20];
    if (argc > 2)
    {
        ptr = fopen(argv[2], "r");
    }
    else
    {
        printf("C-Advanced, HK20152\n");
        exit(0);
    }
    if (ptr != NULL)
    {
        fscanf(ptr, "%d%*c", &vertex);
        printf("vertex = %d\n", vertex);
        while (i != vertex)
        {
            fscanf(ptr, "%d%[^\n]%*c", &a, s);
            addVertex(g, a, s);
            //printf("%d\t%s\n", a, s);
            i++;
        }
        i = 0;
        fscanf(ptr, "%d%*c", &edge);
        printf("edge = %d\n", edge);
        while (i != edge)
        {
            fscanf(ptr, "%d%d%lf%*c", &a, &b, &c);
            addEdge(g, a, b, c);
            //printf("%d\t%d\t%lf\n", a, b, c);
            i++;
        }
        choose = readCommand(argc, argv);
        switch (choose)
        {
        case 2:
            InCase2(g);
            break;
        case 3:
            printf("%g", getEdgeValue(g, atoi(argv[3]), atoi(argv[4])));
            break;
        case 4:
            shortestPath(g, atoi(argv[3]), atoi(argv[4]));
            break;
        case 5:
            list = incomingVertices(g, atoi(argv[3]));
            Dllist node = list;
            int k = 0;
            dll_traverse(node, list)
            {
                if (dll_next(node) != NULL)
                {
                    k++;
                }
            }
            printf("%d\n", k);
            dll_traverse(p, list)
            {
                printf("%d\t", jval_i(p->val));
                printf("%s\t", getVertexName(g, jval_i(p->val)));
                printf("%lf\n", getEdgeValue(g, argv[3], jval_i(p->val)));
            }
            printf("\n");
            break;
        case 6:

            break;
        case 7:
            dropGraph(g);
            exit(0);
            break;
        default:
            break;
        }
    }

    return 0;
}
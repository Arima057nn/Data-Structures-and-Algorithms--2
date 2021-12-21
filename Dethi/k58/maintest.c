#include "library.h"

int readCommand(int argc, char *agrv[])
{
    if (strcmp(agrv[0], "./pr") != 0)
    {
        printf("Ten file bi sai\n");
        exit(0);
    }
    if (argc == 5)
    {
        if (strcmp(agrv[1], "cc") == 0)
            return 3;
        if (strcmp(agrv[1], "cr") == 0)
            return 4;
    }

    if (argc == 4)
    {
        if (strcmp(agrv[1], "i2n") == 0)
            return 1;
        if (strcmp(agrv[1], "n2i") == 0)
            return 2;
        if (strcmp(agrv[1], "odg") == 0)
            return 5;
        if (strcmp(agrv[1], "rel") == 0)
            return 6;
    }
}

int main(int argc, char *argv[])
{
    FILE *ptr;
    Dllist list, p;
    JRB node;
    Graph g = createGraph();
    int choose, vertex, edge;
    int i = 0, a, b, n;
    double c;
    int M[100], N[100];
    char s[20];
    if (argc == 2)
    {
        if (strcmp(argv[1], "help") == 0)
            printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
        if (strcmp(argv[1], "about") == 0)
            printf("C advanced 20142 final exam.\n");
        exit(0);
    }
    if (argc > 2)
    {
        ptr = fopen(argv[2], "r");
    }
    if (ptr != NULL)
    {
        fscanf(ptr, "%d%d%*c", &vertex, &edge);
        while (i != vertex)
        {
            fscanf(ptr, "%s%d%*c", s, &a);
            addVertex(g, a, s);
            //printf("%d\t%s\n", a, s);
            i++;
        }
        while (fscanf(ptr, "%d%d%*c", &a, &b) == 2)
        {
            addEdge(g, a, b);
            //printf("%d\t%d\n", a, b);
        }
        choose = readCommand(argc, argv);
        switch (choose)
        {
        case 1:
            printf("\n%s\n", getVertexName(g, atoi(argv[3])));
            break;
        case 2:
            printf("%d\n", getVertexId(g, argv[3]));
            break;
        case 3:
            list = outgoingVertices(g, atoi(argv[3]));
            dll_traverse(p, list)
            {
                a = hasEdge(g, atoi(argv[4]), jval_i(p->val));
                if (a == 1)
                {
                    printf("%s\n", getVertexName(g, jval_i(p->val)));
                }
            }
            break;
        case 4:
            list = incomingVertices(g, atoi(argv[3]));
            dll_traverse(p, list)
            {
                a = hasEdge(g, jval_i(p->val), atoi(argv[4]));
                if (a == 1)
                {
                    printf("%s\n", getVertexName(g, jval_i(p->val)));
                }
            }
            break;
        case 5:
            jrb_traverse(node, g.edges)
            {
                if (outdegree(g, jval_i(node->key), M) > atoi(argv[3]))
                {
                    printf("%s\n", getVertexName(g, jval_i(node->key)));
                }
            }

            break;
        case 6:
            list = outgoingVertices(g, atoi(argv[3]));
            dll_traverse(p, list)
            {
                printf("%s\n", getVertexName(g, jval_i(p->val)));
                n = outdegree(g, jval_i(p->val), N);
                //printf("%d\t%d\n",N[0] ,jval_i(p->val));
                for (i = 0; i < n; i++)
                {
                    printf("%s\n", getVertexName(g, N[i]));
                }
            }
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
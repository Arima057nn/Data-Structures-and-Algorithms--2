#include "library.h"

void InCase2(Graph graph)
{
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.edges)
    {
        printf("%d %s\n", jval_i(node1->key), getVertexName(graph, jval_i(node1->key)));
    }
}

int main()
{
    FILE *ptr;
    Dllist p, list;
    int choose;
    int i = 0, vertex, edge;
    JRB node;
    int a, b;
    double c;
    char s[20];
    Graph g = createGraph();
    while (1)
    {
        printf("======== MENU ========\n"
               "1. \n"
               "2. \n"
               "3. \n"
               "4. \n"
               "5. \n"
               "6. \n"
               "7. \n"
               "--> Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            ptr = fopen("/home/tttt/Arima/C_Advance/Dethi/k59/exam.txt", "r");
            if (ptr == NULL)
            {

                printf("cannot open the file\b");
                return 1;
            }
            fscanf(ptr, "%d%*c", &vertex);

            while (i != vertex)
            {
                fscanf(ptr, "%d%[^\n]%*c", &a, s);
                addVertex(g, a, s);
                printf("%d\t%s\n", a, s);
                i++;
            }
            i = 0;
            fscanf(ptr, "%d%*c", &edge);
            while (i != edge)
            {
                fscanf(ptr, "%d%d%lf%*c", &a, &b, &c);
                addEdge(g, a, b, c);
                printf("%d\t%d\t%lf\n", a, b, c);
                i++;
            }

            fclose(ptr);

            break;
        case 2:
            printf("%g", getEdgeValue(g, 1, 3));

            /*  list = incomingVertices(g, 1);
            dll_traverse(p, list)
            {
                printf("%4d", jval_i(p->val));
            }
            printf("\n"); */
            break;
        case 3:
            printf("Nhap s:");
            scanf("%d", &a);
            printf("Nhap t:");
            scanf("%d", &b);
            shortestPath(g, a, b);

            //BFS(g, 1, -1, printfVertex);
            break;
        case 4:
            scanf("%d",&a);
            list = incomingVertices(g, a);
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
                printf("%g\n", getEdgeValue(g, a, jval_i(p->val)));
            }
            printf("\n");
            break;
        case 5:
            BFS(g,1,-1,printfVertex);
            break;

        case 6:
            InCase2(g);
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

//gcc -I ../Libfdr/ -o GK GK.c graph_jrb.c ../Libfdr/libfdr.a
// ./GK
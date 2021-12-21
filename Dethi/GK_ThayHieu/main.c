#include "library.h"

int compare_i(Jval *a, Jval *b)
{
    if (jval_i(*a) == jval_i(*b))
        return 0;
    else if (jval_i(*a) < jval_i(*b))
        return -1;
    else
        return 1;
}

void printfVertex(int v)
{
    printf("%4d", v);
}

int compare(void const *item1, void const *item2)
{
    int m, n;
    m = *((int *)item1);
    n = *((int *)item2);
    if (m == n)
        return 0;
    else if (m < n)
        return -1;
    else
        return 1;
}

void init(int a[][10])
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            a[i][j] = 0;
        }
    }
}

void add_edge(int a[][10], int i, int j, double c)
{
    a[i][j] = a[j][i] = c;
}
void printTable(int matrix[][10], int V)
{
    int i, j;
    printf("\n\t");
    for (i = 1; i <= V; i++)
    {
        printf("%d\t", i);
    }
    printf("\n---------------------------------------------------------------------\n");
    for (i = 1; i <= V; i++)
    {
        printf("%d|\t", i);
        for (j = 1; j <= V; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void bai3a(Graph g)
{
    Dllist list, p;
    JRB node;
    jrb_traverse(node, g.vertices)
    {
        printf("Vertex %d: ", jval_i(node->key));
        list = incomingVertices(g, jval_i(node->key));
        dll_traverse(p, list)
        {
            if (getEdgeValue(g, jval_i(node->key), jval_i(p->val)) >= 50)
            {
                printf("%4d", jval_i(p->val));
            }
        }
        printf("\n");
        free_dllist(list);
    }
}
int main()
{
    FILE *ptr;
    Dllist list, p;
    int choose;
    int osiro, michi, a, b;
    double c;
    int i, j, V, s, t;
    JRB node;
    int matrix[10][10];
    init(matrix);
    Graph g = createGraph();
    Graph gh;
    int output[10];
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
            ptr = fopen("/home/tttt/Arima/C_Advance/GK_ThayHieu/dothi.txt", "r");
            if (ptr == NULL)
            {

                printf("cannot open the file\b");
                return 1;
            }
            fscanf(ptr, "%d%d%*c", &osiro, &michi);
            V = osiro;
            while (fscanf(ptr, "%d%*c%d%*c%lf%*c", &a, &b, &c) == 3)
            {
                //printf("%-20d %-20d %-20f\n", a, b, c);
                addEdge(g, a, b, c);
                addVertex(g, a, "1");
                addVertex(g, b, "1");
                add_edge(matrix, a, b, c);
                //matrix[a][b] = matrix[b][a] = c;
            }
            printTable(matrix, V);
            //fclose(ptr);

            break;
        case 2:
            jrb_traverse(node, g.vertices)
            {
                printf("Castle %d: ", jval_i(node->key));
                list = incomingVertices(g, jval_i(node->key));
                dll_traverse(p, list)
                {
                    printf("%4d", jval_i(dll_val(p)));
                }
                printf("\n");
                free_dllist(list);
            }

            /*  list = incomingVertices(g, 1);
            dll_traverse(p, list)
            {
                printf("%4d", jval_i(p->val));
            }
            printf("\n"); */
            break;
        case 3:
            bai3a(g);
            printf("\n");

            break;
        case 4:
            printf("Nhap s:");
            scanf("%d", &s);
            printf("Nhap t:");
            scanf("%d", &t);
            shortestPath(g, s, t);

            break;
        case 5:
            gh = createGraph();
            rewind(ptr);
            fscanf(ptr, "%d%d%*c", &osiro, &michi);

            while (fscanf(ptr, "%d%*c%d%*c%lf%*c", &a, &b, &c) == 3)
            {
                //printf("%-20d %-20d %-20f\n", a, b, c);
                if (c >= 50)
                {
                    addEdge(gh, a, b, c);
                    addVertex(gh, a, "1");
                    addVertex(gh, b, "1");
                    add_edge(matrix, a, b, c);
                }
            }
            printf("Nhap s:");
            scanf("%d", &s);
            printf("Nhap t:");
            scanf("%d", &t);
            shortestPath(gh, s, t);
            dropGraph(gh);
            break;

        case 6:

            break;
        case 7:
            dropGraph(g);
            fclose(ptr);
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
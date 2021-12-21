#include "library.h"

typedef struct
{
    char sp[20];
} SP;

Dllist case4(Graph g, int v) //cac
{
    JRB node, l, i;
    Dllist output = new_dllist();

    if ((node = jrb_find_int(g.edges, v)) == NULL)
        return output;

    l = (JRB)jval_v(node->val);
    jrb_traverse(i, l)
    {
        if (jval_i(i->key) < 0)
        {
            dll_append(output, i->key);
        }
    }
    return output;
}

Dllist case5(Graph g, int v) //cac
{
    JRB node, l, i;
    Dllist output = new_dllist();

    if ((node = jrb_find_int(g.edges, v)) == NULL)
        return output;

    l = (JRB)jval_v(node->val);
    jrb_traverse(i, l)
    {
        if (jval_i(i->key) > 0)
        {
            dll_append(output, i->key);
        }
    }
    return output;
}

int readCommand(int argc, char *agrv[])
{
    if (strcmp(agrv[0], "./qlykhang") != 0)
    {
        printf("Ten file bi sai\n");
        exit(0);
    }
    if (argc == 3)
    {
        return 2;
    }
    if (argc == 6)
    {
        if (strcmp(agrv[1], "-w") == 0)
            return 3;
        if (strcmp(agrv[1], "-h") == 0)
            return 5;
    }
    if (argc == 4)
    {
        return 4;
    }

    if (argc == 8)
    {
        return 6;
    }
}

int readFile1(FILE *ptr)
{
    int a, n;
    char s[30];
    int i = 0;
    fscanf(ptr, "%d%*c", &n);
    while (i != n)
    {
        fscanf(ptr, "%s%d%*c", s, &a);
        //addVertex(g, a, s);
        printf("%s\t%d\n", s, a);
        i++;
    }
    return n;
}

int readFile2(FILE *fptr, FILE *ptr, Graph g, int M[])
{
    int a, b, vertex, edge;
    double c;
    char s[20];
    int i = 0, j = 0;
    SP *sp;
    int n;
    int A[10];
    fscanf(ptr, "%d%*c", &n);
    sp = (SP *)malloc(n * sizeof(SP));
    while (i != n)
    {
        fscanf(ptr, "%s%d%*c", sp[i + 1].sp, &A[i + 1]);
        //addVertex(g, a, s);
        //printf("%s\t%d\n", sp[i+1].sp, A[i+1]);
        i++;
    }
    i = 0;
    fscanf(fptr, "%d%*c", &vertex);
    while (i != vertex)
    {
        fscanf(fptr, "%s%d%*c", s, &M[i + 1]);
        addVertex(g, M[i + 1], s);
        //printf("%d\t%s\n", a, s);

        while (j != n)
        {
            fscanf(fptr, "%d%lf%*c", &b, &c);
            //printf("%s\t%d\t%g\n", sp[j+1].sp,-b, c);
            addVertex(g, -b, sp[j + 1].sp);
            addEdge(g, M[i + 1], -b, c);
            j++;
        }
        j = 0;
        i++;
    }
    fscanf(fptr, "%d%*c", &edge);
    while (fscanf(fptr, "%d%d%lf%*c", &a, &b, &c) == 3)
    {
        addEdge(g, a, b, c);
        //printf("%d\t%d\t%g\n",a,b,c);
    }
    return vertex;
}
void time(double t)
{
    int i;
    int a = t / 60;
    double b = t - a * 60;
    printf("thoi gian van chuyen la %d gio %g phut", a, b);
}
int main(int argc, char *argv[])
{
    FILE *ptr, *fptr;
    Dllist p, list;
    Graph g = createGraph();
    int choose;
    int soSP, soKH;
    int a, b, i;
    double c, t;
    int M[10];
    char s[20];

    if (argc > 2)
    {
        if (argc == 3)
        {
            ptr = fopen(argv[2], "r");
            soSP = readFile1(ptr);
            exit(0);
        }
        if (argc > 3)
        {
            fptr = fopen(argv[2], "r");
            ptr = fopen(argv[3], "r");
        }
        if (ptr == NULL)
        {
            printf("Cannot open the file %s !", argv[2]);
            exit(0);
        }
    }
    else
    {
        printf("C-Advanced, HK20182\n");
        exit(0);
    }
    if (ptr != NULL && fptr != NULL)
    {

        choose = readCommand(argc, argv);
        // soSP = readFile11(ptr);
        soKH = readFile2(fptr, ptr, g, M);

        switch (choose)
        {
        case 2:

            break;
        case 3:
            printf("%g\n", getEdgeValue(g, atoi(argv[4]), atoi(argv[5])));
            break;
        case 4:
            for (i = 0; i < soKH; i++)
            {

                list = case4(g, M[i + 1]);
                p = list;
                printf("%s\n", getVertexName(g, M[i + 1]));
                dll_traverse(p, list)
                {
                    printf("%s\t%g\n", getVertexName(g, jval_i(p->val)), getEdgeValue(g, jval_i(p->val), M[i + 1]));
                }
            }
            /*  list = outgoingVertices(g, 1);
            p = list;
            printf("%s\n", getVertexName(g, 1));
            dll_traverse(p, list)
            {
                printf("%s\t%g\n", getVertexName(g, jval_i(p->val)), getEdgeValue(g, jval_i(p->val), 1));
            } */

            break;
        case 5:
            printf("%s\n", getVertexName(g, atoi(argv[5])));

            printf("%s\t%g", getVertexName(g, -atoi(argv[4])), getEdgeValue(g, atoi(argv[5]), -atoi(argv[4])));
            printf("\n--- Cac kho ke la: \n");

            list = case5(g, atoi(argv[5]));
            p = list;

            dll_traverse(p, list)
            {
                printf("%s\n%s\t%g\n", getVertexName(g, jval_i(p->val)), getVertexName(g, -atoi(argv[4])), getEdgeValue(g, jval_i(p->val), -atoi(argv[4])));
            }

            break;
        case 6:
            if (getEdgeValue(g, atoi(argv[6]), -atoi(argv[4])) >= 10)
            {
                printf("Dat hang thanh cong, thoi gian giao hang la 30p\n");
            }
            else
            {
                if (getEdgeValue(g, atoi(argv[6]), -atoi(argv[4])) + getEdgeValue(g, atoi(argv[7]), -atoi(argv[4])) > 10)
                {
                    printf("Dat hang thanh cong, \n");
                    t = (getEdgeValue(g, atoi(argv[6]), atoi(argv[7])) * 60) / 30 + 30;
                    printf("%lf", t);
                    time(t);
                }
                else
                {
                    printf("Dat hang khong thanh cong");
                }
            }
            break;
        default:
            break;
        }
    }
    dropGraph(g);
    return 0;
}
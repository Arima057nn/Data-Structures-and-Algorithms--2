#include "library.h"

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
        return 3;
    }
    if (argc == 4)
    {
        return 4;
    }
    if (argc == 5)
    {
        return 5;
    }
    if (argc == 8)
    {
        return 6;
    }
}

int readFile1(FILE *ptr)
{
    int a, n;
    double c;
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

int readFile11(FILE *ptr)
{
    int a, n;
    double c;
    char s[30];
    int i = 0;
    fscanf(ptr, "%d%*c", &n);
    while (i != n)
    {
        fscanf(ptr, "%s%d%*c", s, &a);
        //addVertex(g, a, s);
        //printf("%s\t%d\n", s, a);
        i++;
    }
    return n;
}

void readFile2(FILE *ptr, Graph g, int n)
{
    int a, b, vertex, edge;
    double c;
    char s[20];
    int i = 0, j = 0;
    fscanf(ptr, "%d%*c", &vertex);

    while (i != vertex)
    {
        fscanf(ptr, "%s%d%*c", s, &a);
        addVertex(g, a, s);
        //printf("%d\t%s\n", a, s);
        while (j != n)
        {
            fscanf(ptr, "%d%d%*c", &a, &b);
            j++;
        }
        j = 0;
        i++;
    }
    fscanf(ptr, "%d%*c", &edge);
    while (fscanf(ptr, "%d%d%lf%*c", &a, &b, &c) == 3)
    {
        addEdge(g, a, b, c);
        //printf("%d\t%d\t%g\n",a,b,c);
    }
}
int main(int argc, char *argv[])
{
    FILE *ptr, *fptr;
    Dllist p, list;
    Graph g = createGraph();
    int choose;
    int soSP;
    int a, b;
    double c;
    char s[20];
    //int **M;
    // M = (int **)malloc(n * sizeof(int *));
    // M[i] = (int *)calloc(n + 1, sizeof(int));
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
        soSP = readFile11(ptr);
        //M = (int **)malloc((soSP+1) * sizeof(int *));
        readFile2(fptr, g, soSP,M);


        switch (choose)
        {
        case 2:

            break;
        case 3:
            printf("%g\n", getEdgeValue(g, atoi(argv[4]), atoi(argv[5])));
            break;
        case 4:
            break;
        case 5:

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
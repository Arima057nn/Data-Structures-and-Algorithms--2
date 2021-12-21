#include "graph_jrb.h"
#define sizemax 100
int main()
{
    FILE *ptr;
    char A[sizemax], B[sizemax];
    Graph g = createGraph();
    int i = 0,vertex = 0,  n;
    int choose;
    Jval list[100][2];
    while (1)
    {
        printf("1. \n"
               "2. \n"
               "3. \n"
               "--> Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            

            if ((ptr = fopen("/home/tttt/Arima/C_Advance/Thi_GK/NH.txt", "r")) == NULL)
            {
                printf("Cannot open NH.txt file!\n");
                return 1;
            }
            fscanf(ptr, "%d%*c", &n);
            while (fscanf(ptr, "%*c%[^\"]%*c%*c%[^\"]%*c%*c", A, B) == 2)
            {
                i++;
                addEdge(g, A, B, &vertex, list);
                printf("%-20s %-20s\n",A,B);
            }
            printf("%d",i);
            fclose(ptr);
            break;
        case 2:

            break;
        case 3:
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
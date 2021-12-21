#include "library.h"
#include <ctype.h>
int getID(char *A)
{
    for (int i = 0; i < strlen(A); i++)
        if (isdigit(A[i]))
            return atoi(&A[i]);
}
int main()
{
    FILE *ptr;
    int choose;
    int dest, soucre;
    double time;
    char A[100], B, C = '\n';
    Graph g = createGraph();
    while (1)
    {
        printf("\n======== MENU ========\n"
               "1. \n"
               "2. \n"
               "3. \n"
               "4. \n"
               "5. \n"
               "6. \n"
               "--> Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            ptr = fopen("exam.txt", "r");
            if (ptr == NULL)
            {
                printf("Cannot open the file");
                return 1;
            }
            while (!feof(ptr))
            {
                fscanf(ptr, "%s%*c%*c%c", A, &B);
                dest = getID(A);
                addVertex(g, dest, A);
                while ((B != C) && (!feof(ptr)))
                {
                    fscanf(ptr, "%[^-]%*c%lf", A, &time);
                    soucre = getID(A);
                    addVertex(g, soucre, A);
                    addEdge(g, soucre, dest, time);
                    fscanf(ptr, "%c", &B);
                }
            }

            fclose(ptr);

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            break;
        case 5:

            break;

        case 6:
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define VOCUC 9999999
#define size 6

typedef struct Graph
{
    JRB Egde;
    JRB Vertex;
}Graph;

int main()
{
    int luaChon;

    int *output = malloc(100*sizeof(int));
    char name[20][100] = {};
    Graph graph = createGraph();
    FILE *taptin = fopen("", "r+");
    JRB node1 = NULL, node2 = NULL;
    if(taptin != NULL)
    {


        while(1)
        {
            {//menu
                printf("\nNhap 1 de:\n");
                printf("Nhap 2 de: \n");
                printf("Nhap 3 de: \n");
                printf("Nhap 4 de: \n");
                printf("Nhap 5 de: \n");
                printf("Nhap 6 de:\n");
                printf("Nhap 7 de: Thoat chuong trinh\n");
                printf("Nhap de: ");
                scanf("%d", &luaChon);
                while(getchar() != '\n');
            }
            if(luaChon == 7)
            {
                fclose(taptin);
                exit(1);
            }
            else if(luaChon < 1 || luaChon > 7)
            {
                printf("Nhap cac so tu 1 -> 7\n");
                continue;
            }
            switch(luaChon)
            {
                case 1:
                {

                    break;
                }
                case 2:
                {

                    break;
                }


            }
        }
        fclose(taptin);
    }
    else
    {
        printf("ERROR\n");
    }
    return 0;
}

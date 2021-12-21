#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define VOCUC 9999
#define size 6

typedef struct Graph
{
    JRB Egde;
    JRB Vertex;
}Graph;

Graph createGraph();

void readFile(Graph graph, FILE *taptin)
{
    int chuyenHuong;
    char str[100];
    char *tmp1, *tmp2;

    for(; fgets(str, 98, taptin) != NULL; chuyenHuong = 0)
    {
        str[strlen(str) - 1] = '\0';
        if((tmp1 = strstr(str, "=")) != NULL)
        {
            *tmp1 = '\0';
            tmp1 += 2;
            printf("%s ", str);
            tmp1[strlen(tmp1) - 1] = '\0';
            printf("%s\n", tmp1);
        }
        else
        {
            tmp1 = strstr(str, " ");
            *tmp1 = '\0';
            tmp1 ++;
            printf("%s ", str);
            tmp2 = tmp1;

            tmp1 = strstr(tmp1, " ");
            *tmp1 = '\0';
            tmp1++;
            printf("%s ", tmp2);
            tmp2 = tmp1;

            printf("%.1f\n", atof(tmp2));
        }


    }

}

int main()
{
    FILE *taptin = fopen("input.txt", "r+");
    if(taptin == NULL)
    {
        printf("EROOR\n");
        exit(1);
    }
    Graph graph = createGraph();
    readFile(graph, taptin);
}


Graph createGraph()
{
    Graph graph;
    graph.Egde = make_jrb();
    graph.Vertex = make_jrb();
    return graph;
}



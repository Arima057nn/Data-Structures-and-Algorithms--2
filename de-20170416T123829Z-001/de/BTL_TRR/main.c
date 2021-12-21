#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define VOCUC 9999999
#define MAX_SIZE 30

typedef struct Graph
{
    JRB Egde;
    JRB Vertex;
}Graph;

Graph createGraph();

int readFile(FILE *taptin, Graph nuoc, char name[][100]);
void addEdge(Graph graph, int v1, int v2, int trongSo);
void addVertex(Graph graph, int id, char* name);
void addEgdeConLai(Graph graph);
int convertIJtokey(int i, int j, char name[][100]);
void convertAtoIJ(char *array, int *hang, int *cot);
char *convertItoA(int key, char name[][100]);
int convertAtoI(char *array, char name[][100]);
void DFS_lt(Graph graph, int v1, int v2, int *daXet, int *output, int *soPT);
int riaMT(int i, int j);
void In(Graph graph, char name[][100]);
int tinhDienTich(Graph graph);


int main()
{
    Graph nuoc = createGraph();
    char name[20][100] = {};

    FILE *taptin = fopen("input.txt", "r+");
    JRB node1 = NULL, node2 = NULL;
    int *output = malloc((MAX_SIZE*MAX_SIZE)*sizeof(int));
    int daXet[MAX_SIZE*MAX_SIZE] = {};
    int i1, soPT = 0, h1, c1;
    char *ten = malloc(sizeof(char)*30);
    int chuVi = 0, chuViMax, chuViHo;
    if(taptin == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
    chuViMax = readFile(taptin, nuoc, name);

    for(i1 = 0; i1 < MAX_SIZE*MAX_SIZE; i1++)
    {
        daXet[i1] = 0;
    }
    soPT = 0;
    jrb_traverse(node1, nuoc.Egde)
    {
        ten = convertItoA(jval_i(node1->key), name);
        convertAtoIJ(ten, &h1, &c1);
        if(daXet[jval_i(node1->key)] == 0 && riaMT(h1 , c1))
        {
            DFS_lt(nuoc, convertIJtokey(h1, c1, name), -1, daXet, output, &soPT);


        }
    }
    //printf("Truoc khi xoa node bien\n");
    //In(nuoc, name);
    for(i1 = 0, node1 = NULL, node2 = NULL; i1 < soPT; i1++, node1 = NULL, node2 = NULL)
    {
        node1 = jrb_find_int(nuoc.Egde, output[i1]);
        if(node1 == NULL) continue;
        jrb_delete_node(node1);

        node2 = jrb_find_int(nuoc.Vertex, output[i1]);
        if(node2 == NULL) continue;
        jrb_delete_node(node2);
    }
    //printf("\nCac dinh ho\n");
    //In(nuoc, name);
    printf("\nChu vi max: %d\n", chuViMax);
    chuViHo = tinhDienTich(nuoc);
    printf("\nChu vi ho: %d\n", chuViHo);
    chuVi = chuViMax - chuViHo;
    printf("\nChu vi dat lien: %d\n", chuVi);
    return 1;
}

int tinhDienTich(Graph graph)
{
    int nut = 0, cung = 0;
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Egde)
    {
        nut++;
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            //printf("Cung %d-%d\n", jval_i(node1->key), jval_i(node2->key));
            cung++;
        }
    }
    return nut * 4 - cung;
}


int readFile(FILE *taptin, Graph nuoc, char name[][100])
{
    int bienChayH, bienChayC, key, soDinhDatLien = 0, soCanhDatLien = 0;
    int z, hang, cot;
    int giaTri[MAX_SIZE][MAX_SIZE], i, j;
    JRB node1;
    char tmp;
    fscanf(taptin, "%d", &hang);
    fscanf(taptin, "%c", &tmp);
    fscanf(taptin, "%d", &cot);

    //printf("hang: %d; cot: %d\n", hang, cot);
    //scanf("%d", &bienChayH);
    for(i = 0; i < hang; i++)
    {
        for(j = 0; j < cot; j++)
        {
            fscanf(taptin, "%d", &giaTri[i][j]);
            if(j == cot - 1)
                continue;
            fscanf(taptin, "%c", &tmp);
        }
    }
    for(i = 0; i < hang; i++)
    {
        for(j = 0; j < cot; j++)
        {
            if(giaTri[i][j] == 1)//dat lien
            {
                soDinhDatLien++;
                if(i-1 >= 0 && giaTri[i-1][j] == 1)
                {
                    soCanhDatLien += 2;
                }
                if(j-1 >= 0 && giaTri[i][j-1] == 1)
                {
                    soCanhDatLien += 2;
                }
            }
            else if(giaTri[i][j] == 0)//bien
            {
                key = convertIJtokey(i, j, name);
                node1 = jrb_find_int(nuoc.Vertex, key);
                if(node1 == NULL)
                {
                    JRB node2 = make_jrb();
                    node1 = jrb_insert_int(nuoc.Vertex, key, new_jval_v(node2));
                    if(i-1 >= 0 && giaTri[i-1][j] == 0)
                    {
                        key = convertIJtokey(i-1, j, name);
                        node2 = jrb_find_int(nuoc.Vertex, key);
                        addEdge(nuoc, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(nuoc, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                    if(j-1 >= 0 && giaTri[i][j-1] == 0)
                    {
                        key = convertIJtokey(i, j-1, name);
                        node2 = jrb_find_int(nuoc.Vertex, key);
                        addEdge(nuoc, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(nuoc, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                }
            }
        }
    }

    addEgdeConLai(nuoc);
    return soDinhDatLien * 4 - soCanhDatLien;
}

Graph createGraph()
{
    Graph graph;
    graph.Egde = make_jrb();
    graph.Vertex = make_jrb();
    return graph;
}

int riaMT(int h1, int c1)
{
    int hang, cot;
    FILE *taptin = fopen("input.txt", "r+");
    if(taptin == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
    char tmp;
    fscanf(taptin, "%d", &hang);
    fscanf(taptin, "%c", &tmp);
    fscanf(taptin, "%d", &cot);
    fclose(taptin);

    if((h1 == 0 || h1 == hang-1 || c1 == 0 || c1 == cot-1))
    {
        return 1;
    }

    return 0;
}


void In(Graph graph, char name[][100])
{
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Egde)
    {
        printf("Dinh %s:", convertItoA(jval_i(node1->key), name));
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            printf("  %s", convertItoA(jval_i(node2->key), name));
        }
        printf("\n");
    }
}

void DFS_lt(Graph graph, int v1, int v2, int *daXet, int *output, int *soPT)
{
    if(jrb_find_int(graph.Vertex, v1) == NULL)
    {
        printf("Khong ton tai dinh %d\n", v1);
        return 0;
    }
    int d1, i;
    int CTrinh = 0;
    Dllist stack = new_dllist(), Snode = NULL;
    JRB node1 = NULL, node2 = NULL;
    daXet[v1] = 1;
    dll_prepend(stack, new_jval_i(v1));
    while(!dll_empty(stack))
    {
        Snode = dll_first(stack);
        d1 = jval_i(Snode->val);
        output[*soPT] = d1;
        (*soPT)++;
        dll_delete_node(Snode);
        if(d1 == v2)
        {
            free_dllist(stack);
            return ;
        }
        node1 = jrb_find_int(graph.Egde, d1);
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            if(daXet[jval_i(node2->key)] == 0)
            {
                dll_prepend(stack, node2->key);
                daXet[jval_i(node2->key)] = 1;
            }
            if(jval_i(node2->key) == v1)
            {
               CTrinh = 1;
            }
        }
    }
    free_dllist(stack);
}


int convertAtoI(char *array, char name[][100])
{
    int i = 0;
    static int n = 0;
    for(i=0; i < n; i++)
    {
        if(strcmp(name[i], array) == 0)
        {
            return i;
        }
    }
    strcpy(name[n], array);
    n++;
    return n-1;
}

char *convertItoA(int key, char name[][100])
{
    if(key >= 0)//tranh coredumped
    {
        return name[key];
    }
}

void convertAtoIJ(char *array, int *hang, int *cot)
{
    *hang = *array - '0';
    *cot = *(array+1) - '0';
}

int convertIJtokey(int i, int j, char name[][100])
{
    char c1, c2;
    char *array = malloc(sizeof(char) * 3);
    c1 = i + '0';
    c2 = j + '0';
    *array = c1;
    *(array + 1) = c2;
    *(array + 2) = '\0';
    return convertAtoI(array, name);
}

void addEdge(Graph graph, int v1, int v2, int trongSo)
{
    JRB node = jrb_find_int(graph.Egde, v1), node2 = NULL;
    if(node == NULL)
    {
        JRB node2 = jrb_find_int(graph.Vertex, v1);
        if(node2 == NULL)
        {
            printf("Khong co dinh %d\n", v1);
            return ;
        }
        JRB dsKe = make_jrb();
        jrb_insert_int(dsKe, v2, new_jval_i(trongSo));
        jrb_insert_int(graph.Egde, v1, new_jval_v(dsKe));
    }
    else
    {
        node2 = jrb_find_int((JRB)jval_v(node->val), v2);
        if(node2 == NULL)//neu co canh v1 v2 roi thi khong them nua
        {
            jrb_insert_int((JRB)jval_v(node->val), v2, new_jval_i(trongSo));
        }
    }
}

void addVertex(Graph graph, int id, char* name)
{
    JRB node = jrb_find_int(graph.Vertex, id);
    if(node == NULL)
    {
        jrb_insert_int(graph.Vertex, id, new_jval_s(name));
    }
    else
    {
        strcpy(jval_s(node->val), name);
    }
}

void addEgdeConLai(Graph graph)
{
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Vertex)
    {
        if(jrb_find_int(graph.Egde, jval_i(node1->key)) == NULL)
        {
            JRB dsKe = make_jrb();
            jrb_insert_int(graph.Egde, jval_i(node1->key), new_jval_v(dsKe));
        }
    }
}


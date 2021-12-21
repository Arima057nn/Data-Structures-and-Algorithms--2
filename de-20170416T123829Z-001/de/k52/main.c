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

void YC1(Graph graph, FILE *taptin, char name[][100]);
void YC2(Graph graph, FILE *taptin, char name[][100]);


int DFS(Graph graph, int v1, int v2, void (* func)(int, char *), char name[][100]);
void func(int z, char name[][100]);
int outdegree(Graph graph, int v, int* output);
int indegree(Graph graph, int v, int* output);
void DeQuy(Graph graph, int v, int *output, int daXet[], int *n);
int indegree_Sua(Graph graph, int v, int *output, int *daXet, int *n);
void inThongTin(Graph graph);
void In(Graph graph, char name[][100]);
int getTrongSo(Graph graph, int v1, int v2);
void addEgdeConLai(Graph graph);
int hasEdge(Graph graph, int v1, int v2);
void addEdge(Graph graph, int v1, int v2, int trongSo);
void addVertex(Graph graph, int id, char* name);
char *convertItoA(int key, char name[][100]);
int convertAtoI(char *array, char name[][100]);
Graph createGraph();


void YC1(Graph graph, FILE *taptin, char name[][100])
{
    readFile(graph, taptin, name);
    In(graph, name);
    printf("\n");
    inThongTin(graph);

}

void YC2(Graph graph, FILE *taptin, char name[][100])
{
    int TF = 0, n, i1;
    int *output = malloc(30*sizeof(int));
    int daXet[30] = {};
    char str[10];
    JRB node1;
    printf("Nhap ten cong viec: ");
    fgets(str, 8, stdin);
    str[strlen(str) - 1] = '\0';

    jrb_traverse(node1, graph.Vertex)
    {
        if(strcmp(jval_s(node1->val), str) == 0)
        {
            TF = 1;
        }
    }
    if(TF == 1)
    {
        int v = convertAtoI(str, name);
        n = outdegree(graph, v, output);
        printf("So cong viec ngay truoc: %d\tLa cac cong viec: ", n);
        for(i1 = 0; i1 < n; i1++)
        {
            printf("%s ", convertItoA(output[i1], name));
        }
        printf("\n");
        DFS(graph, v, -1, func, name);
    }
    else
    {
        printf("Cong viec khong co trong chuong trinh\n");

    }
    free(output);
}

int main()
{
    FILE *taptin = fopen("input.txt", "r+");
    char name[20][100] = {};
    if(taptin == NULL)
    {
        printf("Qua trinh mow tap tin bi loi\n");
        exit(1);
    }
    Graph graph = createGraph();
    printf("\n");
    YC1(graph, taptin, name);
    printf("\n");
    YC2(graph, taptin, name);


}

void func(int z, char name[][100])
{
    printf("%s ", convertItoA(z, name));
}


int DFS(Graph graph, int v1, int v2, void (* func)(int, char *), char name[][100])//neu co TH v2 == v1 thi return -1
{
    if(jrb_find_int(graph.Vertex, v1) == NULL)
    {
        printf("Khong ton tai dinh %d\n", v1);
        return 0;
    }
    int daXet[20] = {}, d1, i;int CTrinh = 0;
    Dllist stack = new_dllist(), Snode = NULL;
    JRB node1 = NULL, node2 = NULL;
    daXet[v1] = 1;
    dll_prepend(stack, new_jval_i(v1));
    while(!dll_empty(stack))
    {
        Snode = dll_first(stack);
        d1 = jval_i(Snode->val);
        dll_delete_node(Snode);
        func(d1, name);
        if(d1 == v2)
        {
            free_dllist(stack);
            if(CTrinh == 1)
            {
                return -1;
            }
            return 1;
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
    if(CTrinh == 1)
    {
        return -1;
    }
    return 1;
}

void readFile(Graph graph, FILE *taptin, char name[][100])
{
    char str[100];
    char *tmp1, *tmp2;
	int i1, space, key;

    for(; fgets(str, 98, taptin) != NULL; )
    {
        str[strlen(str) - 1] = '\0';
        tmp1 = strstr(str, " ");
        *tmp1 = '\0';
        //printf("'%s': ", str);
        key = convertAtoI(str, name);
        addVertex(graph, key, strdup(str));
        tmp1 += 3;
        if(*tmp1 == '\0') continue;
        //printf("tmp1: '%s'\n", tmp1);
        for(i1 = 0, space = 0; i1 < strlen(tmp1); i1++)
        {
        	if(tmp1[i1] == ' ') space++;
        }

        tmp2 = tmp1;
        for(i1 = 0; i1 < space; i1++)
        {
        	tmp1 = strstr(tmp1, " ");
        	*tmp1 = '\0';
        	tmp1++;
        	//printf("'%s' ", tmp2);
        	addEdge(graph, key, convertAtoI(tmp2, name), 1);
        	tmp2 = tmp1;
        }
        //printf("'%s'\n", tmp2);

        addEdge(graph, key, convertAtoI(tmp2, name), 1);
    }
    addEgdeConLai(graph);
}


Graph createGraph()
{
    Graph graph;
    graph.Egde = make_jrb();
    graph.Vertex = make_jrb();
    return graph;
}

void inThongTin(Graph graph)
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
    printf("%d nut, %d cung\n", nut, cung);
}

int outdegree(Graph graph, int v, int* output)
{
    JRB node = jrb_find_int(graph.Egde, v);
    int n = 0;
    if(node == NULL)
    {
        printf("Khong co dinh %d\n", v);
    }
    else
    {
        JRB node1 = NULL;
        jrb_traverse(node1, ((JRB)jval_v(node->val)))
        {
            output[n] = jval_i(node1->key);
            n++;
        }
    }
    return n;
}

int indegree(Graph graph, int v, int* output)
{
    JRB node1 = NULL, node2 = NULL;
    int n = 0;
    jrb_traverse(node1, graph.Egde)
    {
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            if(jval_i(node2->key) == v)
            {
                output[n] = jval_i(node1->key);
                n++;
                break;
            }
        }
    }
    return n;
}

int indegree_Sua(Graph graph, int v, int *output, int *daXet, int *n)
{
    int i1, thoat;
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Egde)
    {
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {

            if(jval_i(node2->key) == v)
            {
                if(daXet[jval_i(node1->key)] == 0)
                {
                    output[*n] = jval_i(node1->key);
                    daXet[jval_i(node1->key)] = 1;
                    (*n)++;

                    break;
                }
            }
        }
    }

}


void DeQuy(Graph graph, int v, int *output, int daXet[], int *n)
{
    int i1, banDau = *n, sauDeQuy;
    indegree_Sua(graph, v, output, daXet, n);
    sauDeQuy = *n;
    for(i1 = banDau; i1 < sauDeQuy; i1++)
    {
        DeQuy(graph, output[i1], output, daXet, n);
    }
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

void addEdge(Graph graph, int v1, int v2, int trongSo)
{
    JRB node = jrb_find_int(graph.Egde, v1), node2 = NULL;
    if(node == NULL)
    {
        JRB node2 = jrb_find_int(graph.Vertex, v1);
        if(node2 == NULL)
        {
            //printf("Khong co dinh %d\n", v1);
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

int hasEdge(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph.Egde, v1);
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        JRB node2 = jrb_find_int((JRB)jval_v(node->val), v2);
        if(node2 == NULL)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}


int getTrongSo(Graph graph, int v1, int v2)
{
    JRB node1 = NULL, node2 = NULL;
    node1 = jrb_find_int(graph.Egde, v1);
    if(node1 != NULL)
    {
        node2 = jrb_find_int((JRB)jval_v(node1->val), v2);
        if(node2 != NULL)
        {
            return jval_i(node2->val);
        }
        else
        {
            printf("Dinh %d khong ton tai\n", v2);
            return 0;
        }
    }
    else
    {
        printf("Dinh %d khong ton tai\n", v1);
        return 0;
    }


}


void In(Graph graph, char name[][100])
{
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Egde)
    {
        printf("'%s': ", convertItoA(jval_i(node1->key), name));
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            printf("  '%s'", convertItoA(jval_i(node2->key), name));
        }
        printf("\n");
    }
}


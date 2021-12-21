
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define VOCUC 9999999
#define MAX_SIZE 50

typedef struct Graph
{
    JRB Egde;
    JRB Vertex;
}Graph;

Graph createGraph();
void readFile(FILE *taptin, Graph graph, Graph bien, char name[][100]);
JRB createJRB();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, int trongSo);
//void hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
//int getComponents(Graph graph, void (* func)(int));
//void dropGraph(Graph graph);
//void topo(Graph graph);/*Sap xep topo la: neu co canh u->v thi phai in ra u truoc v*/
void In(Graph graph, char name[][100]);
void InMT(Graph graph, char name[][100]);
void addEgdeConLai(Graph graph);
//int DFS(Graph graph, int v1, int v2, void (* func)(int));
//int BFS(Graph graph, int v1, int v2, void (* func)(int));
//void inVertex(int v);
//void dijkstra(Graph graph, int v1, int v2, void (* func)(int , int , int *, int *, int *));
int getTrongSo(Graph graph, int v1, int v2);//khong ton tai egde -> return 0
//void DTMax(Graph graph);
int inDiemLT(Graph graph, int hang, int cot, void (*func)(int, char *), char name[][100]);
void funcPrint(int key, char name[][100]);
void funcKhongPrint(int key, char name[][100]);
int tonTaiDiem(Graph graph, int d1, int d2, char name[][100]);
int convertAtoI(char *array, char name[][100]);
char *convertItoA(int key, char name[][100]);
void convertAtoIJ(char *array, int *hang, int *cot);
int convertIJtokey(int i, int j, char name[][100]);
void dijkstra(Graph graph, int v1, int v2, void (* func)(int , int , int *, int *, int *, char *), char name[][100]);
void updateD(Graph graph, Dllist Qmin, JRB node2, int *d, int *parents);
Dllist findQmin(Dllist queue, int *d);
void InDuongDi(int v1, int v2, int *d, int *parents, int *soPT, char name[][100]);

void readFile(FILE *taptin, Graph graph, Graph bien, char name[][100])
{
    int bienChayH, bienChayC, key, soDinh = 0;int z, hang, cot;
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
                key = convertIJtokey(i, j, name);
                node1 = jrb_find_int(graph.Vertex, key);
                if(node1 == NULL)
                {
                    JRB node2 = make_jrb();
                    node1 = jrb_insert_int(graph.Vertex, key, new_jval_v(node2));
                    if(i-1 >= 0 && giaTri[i-1][j] == 1)
                    {
                        key = convertIJtokey(i-1, j, name);
                        node2 = jrb_find_int(graph.Vertex, key);
                        addEdge(graph, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(graph, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                    if(j-1 >= 0 && giaTri[i][j-1] == 1)
                    {
                        key = convertIJtokey(i, j-1, name);
                        node2 = jrb_find_int(graph.Vertex, key);
                        addEdge(graph, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(graph, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                }
            }
            else if(giaTri[i][j] == 0)//bien
            {
                key = convertIJtokey(i, j, name);
                node1 = jrb_find_int(bien.Vertex, key);
                if(node1 == NULL)
                {
                    JRB node2 = make_jrb();
                    node1 = jrb_insert_int(bien.Vertex, key, new_jval_v(node2));
                    if(i-1 >= 0 && giaTri[i-1][j] == 0)
                    {
                        key = convertIJtokey(i-1, j, name);
                        node2 = jrb_find_int(bien.Vertex, key);
                        addEdge(bien, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(bien, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                    if(j-1 >= 0 && giaTri[i][j-1] == 0)
                    {
                        key = convertIJtokey(i, j-1, name);
                        node2 = jrb_find_int(bien.Vertex, key);
                        addEdge(bien, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(bien, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                }
            }
        }
    }

    addEgdeConLai(graph);
    addEgdeConLai(bien);
}


int DFS_lt(Graph graph, int v1, int v2, int *daXet)
{
    if(jrb_find_int(graph.Vertex, v1) == NULL)
    {
        printf("Khong ton tai dinh %d\n", v1);
        return 0;
    }
    int d1, i;int CTrinh = 0;
    Dllist stack = new_dllist(), Snode = NULL;
    JRB node1 = NULL, node2 = NULL;
    daXet[v1] = 1;
    dll_prepend(stack, new_jval_i(v1));
    while(!dll_empty(stack))
    {
        Snode = dll_first(stack);
        d1 = jval_i(Snode->val);
        dll_delete_node(Snode);
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

int checkRiaMT(int i, int j)
{
    FILE *taptin = fopen("input.txt", "r+");
    if(taptin != NULL)
    {
        FILE *taptin = fopen("input.txt", "r+");
        char tmp;
        int hang, cot;
        fscanf(taptin, "%d", &hang);
        fscanf(taptin, "%c", &tmp);
        fscanf(taptin, "%d", &cot);
        fclose(taptin);
        //printf("**hang: %d; cot: %d\n", hang, cot);
        if(!(i == 0 || i == hang-1 || j == 0 || j == cot-1))
        {
            return 0;
        }


        return 1;
    }
    return 0;
}

int main()
{
    int luaChon, d1, d2, d3, d4, n, i, j, bienChay, max, tmp, key1, key2, daXet[MAX_SIZE*MAX_SIZE];
    int soThanhPhanLienThong, LT[1000], soDinhLTMax, LTMax, output[MAX_SIZE*MAX_SIZE];
    int dinh[MAX_SIZE][MAX_SIZE];
    char name[20][100] = {};
    char *keyName = malloc(sizeof(char) * 20);
    Graph graph = createGraph();
    Graph bien = createGraph();
    FILE *taptin = fopen("input.txt", "r+");
    JRB node1 = NULL, node2 = NULL;

    if(taptin != NULL)
    {

        readFile(taptin, graph, bien, name);
        printf("Dat Lien: \n");
        In(graph, name);
        printf("\nBien: \n");
        In(bien, name);
        printf("\n");
        InMT(graph, name);



        printf("Dien tich toi da (tinh ca bo ho): %d\n", DTMax(graph));

        for(i = 0; i < MAX_SIZE*MAX_SIZE; i++)
        {
            daXet[i] = 0;
        }

        for(i = 0; i < 30; i++)
        {
            printf("--%s\n", name[i]);
        }printf("\n---------------\n");
        /*for(i = 0; i < 1000; i++)
        {
            LT[i] = 0;
        }*/
        for(i = 0; i < 30; i++)
        {
            printf("--%s\n", name[i]);
        }
        jrb_traverse(node1, bien.Egde)
        {
            keyName = convertItoA(jval_i(node1->key), name);
            printf("'%s' la bien\n", keyName);
            //printf("'%d' la bien\n", keyName);
            /*if(daXet[jval_i(node1->key)] == 0)
            {
                //keyName = convertItoA(jval_i(node1->key), name);
                //printf("%s la bien\n", keyName);scanf("%d", &d4);
                convertAtoIJ(keyName, &i, &j);
                if(checkRiaMT(i, j))
                {
                    //DFS_lt(graph, jval_i(node1->key), -1, daXet);
                    //printf("%s la bien\n", keyName);
                }

            }*/
        }
scanf("%d", &d4);
        for(i = 0; i < MAX_SIZE*MAX_SIZE; i++)
        {
            LT[daXet[i]]++;
        }
        for(i = 0; i < 5; i++)
        {
            if(soDinhLTMax < LT[i])
            {
                soDinhLTMax = LT[i];
                LTMax = i;
            }
        }
        printf("Thanh phan lien thong lon nhat cua do thi co %d dinh: ", soDinhLTMax);
        for(i = 0; i < MAX_SIZE*MAX_SIZE; i++)
        {
            if(daXet[i] == LTMax)
            {
                printf("%s ", convertItoA(i, name));
            }
        }
        printf("\n");
        fclose(taptin);
    }
    else
    {
        printf("ERROR\n");
    }
    return 0;
}


void InDuongDi(int v1, int v2, int *d, int *parents, int *soPT, char name[][100])
{
    int v = v2, bienChay;
    int duongDi[20] = {}, n=0;
    printf("\nDuong di ngan nhat tu %s->%s: ", convertItoA(v1, name), convertItoA(v2, name));
    duongDi[0] = v2;n++;
    while(v != v1)
    {
        //printf("%d ", parents[v]);
        v = parents[v];
        duongDi[n] = v;
        n++;
    }
    for(bienChay = n-1; 0 <= bienChay; bienChay--)
    {
        printf("%s", convertItoA(duongDi[bienChay], name));
        if(bienChay > 0)
        {
            printf("->");
        }
    }
    printf("\n\n");
}

Dllist findQmin(Dllist queue, int *d)
{
    Dllist Qnode = NULL, Qmin = NULL;
    Qnode = dll_first(queue);
    Qmin = Qnode;
    for(; Qnode != dll_last(queue); )
    {
        if(d[jval_i(Qnode->val)] < d[jval_i(Qmin->val)])
        {
            Qmin = Qnode;
        }
        Qnode = dll_next(Qnode);
    }
    Qnode = dll_next(Qnode);
    Qnode = dll_last(queue);//vong while khong den duoc node cuoi
    if(d[jval_i(Qnode->val)] < d[jval_i(Qmin->val)])
    {
        Qmin = Qnode;
    }
    return Qmin;
}

void updateD(Graph graph, Dllist Qmin, JRB node2, int *d, int *parents)
{
    if(d[jval_i(node2->key)] > (d[jval_i(Qmin->val)] + getTrongSo(graph, jval_i(Qmin->val), jval_i(node2->key))))
    {
        d[jval_i(node2->key)] = d[jval_i(Qmin->val)] + getTrongSo(graph, jval_i(Qmin->val), jval_i(node2->key));
        parents[jval_i(node2->key)] = jval_i(Qmin->val);
    }

}

void dijkstra(Graph graph, int v1, int v2, void (* func)(int , int , int *, int *, int *, char *), char name[][100])
{
    int soPT = 0, i;
    int d[20] = {};
    int parents[20] = {};
    for(i=0; i<20; i++)
    {
        d[i] = VOCUC;
    }
    d[v1] = 0;
    parents[v1] = v1;
    Dllist queue = new_dllist(), Qnode = NULL, Qmin = NULL;
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Vertex)
    {
        dll_append(queue, node1->key);
        soPT++;
    }
    while(!dll_empty(queue))
    {
        Qmin = findQmin(queue, d);
        node1 = jrb_find_int(graph.Egde, jval_i(Qmin->val));
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            updateD(graph, Qmin, node2, d, parents);
        }
        dll_delete_node(Qmin);
    }
    func(v1, v2, d, parents, soPT, name);
}



void funcKhongPrint(int key, char name[][100])
{

}

void funcPrint(int key, char name[][100])
{
    printf("%s ", convertItoA(key, name));
}

int inDiemLT(Graph graph, int hang, int cot, void (*func)(int, char *), char name[][100])
{
    if(tonTaiDiem(graph, hang, cot, name) == 0)
    {
        return -1;
    }
    int key = convertIJtokey(hang, cot, name), soLT = 0;
    JRB node1 = jrb_find_int(graph.Egde, key), node2;
    jrb_traverse(node2, ((JRB)jval_v(node1->val)))
    {
        func(jval_i(node2->key), name);
        soLT++;
    }
    return soLT;
}


int tonTaiDiem(Graph graph, int d1, int d2, char name[][100])
{
    JRB node1, node2;
    char *array;
    int hang, cot;
    jrb_traverse(node1, graph.Vertex)
    {
        array = convertItoA(jval_i(node1->key), name);
        convertAtoIJ(array, &hang, &cot);
        if(hang == d1 && cot == d2)
            return 1;
    }
    return 0;
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





int DTMax(Graph graph)
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
    //printf("%d nut, %d cung\n", nut, cung);
    return nut*4-cung;
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
        JRB dsKe = createJRB();
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
            JRB dsKe = createJRB();
            jrb_insert_int(graph.Egde, jval_i(node1->key), new_jval_v(dsKe));
        }
    }
}



JRB createJRB()
{
    return make_jrb();
}

Graph createGraph()
{
    Graph graph;
    graph.Egde = make_jrb();
    graph.Vertex = make_jrb();
    return graph;
}

char *getVertex(Graph graph, int id)
{
    JRB node = jrb_find_int(graph.Vertex, id);
    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        return jval_s(node->val);
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


/*
int chuyenKeyStr(char *str)//khi thi can dung
{
    int traLai = 0;
    if(strcmp(str, "") == 0)
    {
        return 0;
    }
    else if(strcmp(str, "") == 0)
    {
        return 1;
    }

}
*/

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


void InMT(Graph graph, char name[][100])
{
    int hang, cot, i, j;
    int MT[MAX_SIZE][MAX_SIZE];
    int bienChay1, bienChay2;
    JRB node1;

    FILE *taptin = fopen("input.txt", "r+");
    char tmp;
    fscanf(taptin, "%d", &hang);
    fscanf(taptin, "%c", &tmp);
    fscanf(taptin, "%d", &cot);
    fclose(taptin);
    printf("**hang: %d; cot: %d\n", hang, cot);
    for(bienChay1 = 0; bienChay1 < hang; bienChay1++)
    {
        for(bienChay2 = 0; bienChay2 < cot; bienChay2++)
        {
            MT[bienChay1][bienChay2] = 0;
        }
    }
    jrb_traverse(node1, graph.Egde)
    {
        convertAtoIJ(convertItoA(jval_i(node1->key), name), &i, &j);
        MT[i][j] = 1;
    }
    for(bienChay1 = 0; bienChay1 < hang; bienChay1++)
    {
        for(bienChay2 = 0; bienChay2 < cot; bienChay2++)
        {
            printf("%d ", MT[bienChay1][bienChay2]);
        }printf("\n");
    }
    printf("\n");
}

int cachDi(Graph graph, int v1, int v2, char name[][100], int daXet[])
{
    int sum = 0;int z;
    if(v1 == v2)
    {
        printf("++\n");
        sum++;
        return sum;
    }
    else
    {
        JRB node1 = jrb_find_int(graph.Egde, v1), node2;
        if(node1 != NULL)
        {
            jrb_traverse(node2, ((JRB)jval_v(node1->val)))
            {
                if(daXet[jval_i(node2->key)] == 0)
                {
        printf("%s->%s\n", convertItoA(jval_i(node1->key), name), convertItoA(jval_i(node2->key), name));
        //scanf("%d", &z);
                    daXet[jval_i(node2->key)] = 1;
                    sum += cachDi(graph, jval_i(node2->key), v2, name, daXet);
                    daXet[jval_i(node2->key)] = 0;
                }

            }
        }
    }
    return sum;
}

void In(Graph graph, char name[][100])
{
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Egde)
    {
        printf("Dinh '%s':", convertItoA(jval_i(node1->key), name));
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            printf("  '%s'", convertItoA(jval_i(node2->key), name));
        }
        printf("\n");
    }
}

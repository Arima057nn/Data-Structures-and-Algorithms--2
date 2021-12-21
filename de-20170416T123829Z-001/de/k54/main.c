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

Graph createGraph();
void readFile(taptin, graph);
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
int DFS_lt(Graph graph, int v1, int v2, int *daXet, int soThanhPhanLienThong);
//int BFS(Graph graph, int v1, int v2, void (* func)(int));
//void inVertex(int v);
int getTrongSo(Graph graph, int v1, int v2);//khong ton tai egde -> return 0
//void inThongTin(Graph graph);
int inDiemLT(Graph graph, int hang, int cot, void (*func)(int, char *), char name[][100]);
void funcPrint(int key, char name[][100]);
void funcKhongPrint(int key, char name[][100]);
int tonTaiDiem(Graph graph, int h1, int c1, char name[][100]);
int convertAtoI(char *array, char name[][100]);
char *convertItoA(int key, char name[][100]);
void convertAtoIJ(char *array, int *hang, int *cot);
int convertIJtokey(int i, int j, char name[][100]);
void dijkstra(Graph graph, int v1, int v2, void (* func)(Graph, int , int , int *, int *, int *, char *), char name[][100]);
void updateD(Graph graph, Dllist Qmin, JRB node2, int *d, int *parents);
Dllist findQmin(Dllist queue, int *d);
void InDuongDi(Graph graph, int v1, int v2, int *d, int *parents, int *soPT, char name[][100]);
void inNigekata(Graph graph, int v1, int v2, int *d, int *parents, int *soPT, char name[][100]);
void InDijkstr(Graph graph, int v1, int v2, int *d, int *parents, int *soPT);//khogn can dung v2;

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


int main()
{
    int luaChon, h1, c1, h2, c2, n, i, j, bienChay, max, tmp, key1, key2, daXet[20] = {};
    int soThanhPhanLienThong, LT[5], soDinhLTMax, LTMax;
    int *output = malloc(100*sizeof(int)), dinh[size][size];
    char name[20][100] = {};
    Graph graph = createGraph();
    FILE *taptin = fopen("mecung.txt", "r+");
    JRB node1 = NULL, node2 = NULL;
    if(taptin != NULL)
    {

        readFile(taptin, graph, name);
        In(graph, name);
        printf("\n");
        InMT(graph, name);
        while(1)
        {
            {//menu
                printf("\nNhap 1 de: Doc file va in ma tran\n");
                printf("Nhap 2 de: In so nut va so cung\n");
                printf("Nhap 3 de: In ra diem lien thong\n");
                printf("Nhap 4 de: Tim duong di ngan nhat\n");
                printf("Nhap 5 de: 逃げ方\n");
                printf("Nhap 6 de: In ra thanh phan lien thong lon nhat cua do thi\n");
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
                    printf("\n");
                    InMT(graph, name);
                    break;
                }
                case 2:
                {
                    inThongTin(graph);
                    break;
                }
                case 3:
                {
                    printf("Nhap diem: \n");
                    printf("Hang: ");
                    scanf("%d", &h1);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &c1);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, h1, c1, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", h1, c1);
                        continue;
                    }

                    printf("Diem lien thong cua dinh %d%d: ", h1, c1);
                    inDiemLT(graph, h1, c1, funcPrint, name);
                    printf("\n");
                    break;
                }
                case 4:
                {
                    printf("Nhap diem xuat phat: \n");
                    printf("Hang: ");
                    scanf("%d", &h1);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &c1);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, h1, c1, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", h1, c1);
                        continue;
                    }

                    printf("Nhap diem dich: \n");
                    printf("Hang: ");
                    scanf("%d", &h2);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &c2);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, h2, c2, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", h2, c2);
                        continue;
                    }

                    key1 = convertIJtokey(h1, c1, name);
                    key2 = convertIJtokey(h2, c2, name);
                    dijkstra(graph, key1, key2, InDuongDi, name);
                    break;
                }
                case 5:
                {
                    printf("Nhap 入口: \n");
                    printf("Hang: ");
                    scanf("%d", &h1);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &c1);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, h1, c1, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", h1, c1);
                        continue;
                    }
                    if(!(h1 == 0 || h1 == size-1 || c1 == 0 || c1 == size-1))
                    {
                        printf("Dinh %d%d khong phai la 入口\n", h1, c1);
                        continue;
                    }
                    dijkstra(graph, convertIJtokey(h1, c1, name), -1, inNigekata, name);
                    break;
                }
                case 6:
                {
                    for(i = 0; i < 20; i++)
                    {
                        daXet[i] = 0;
                    }
                    for(i = 0; i < 5; i++)
                    {
                        LT[i] = 0;
                    }
                    soDinhLTMax = 0;
                    soThanhPhanLienThong = 1;
                    jrb_traverse(node1, graph.Egde)
                    {
                        if(daXet[jval_i(node1->key)] == 0)
                        {
                            DFS_lt(graph, jval_i(node1->key), -1, daXet, soThanhPhanLienThong);
                            soThanhPhanLienThong++;
                        }
                    }


                    for(i = 0; i < 20; i++)
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
                    for(i = 0; i < 20; i++)
                    {
                        if(daXet[i] == LTMax)
                        {
                            printf("%s ", convertItoA(i, name));
                        }
                    }
                    printf("\n");
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

int DFS_lt(Graph graph, int v1, int v2, int *daXet, int soThanhPhanLienThong)
{
    if(jrb_find_int(graph.Vertex, v1) == NULL)
    {
        printf("Khong ton tai dinh %d\n", v1);
        return 0;
    }
    int d1, i;int CTrinh = 0;
    Dllist stack = new_dllist(), Snode = NULL;
    JRB node1 = NULL, node2 = NULL;
    daXet[v1] = soThanhPhanLienThong;
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
                daXet[jval_i(node2->key)] = soThanhPhanLienThong;
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


void InDijkstr(Graph graph, int v1, int v2, int *d, int *parents, int *soPT)//khogn can dung v2
{
    int i;
    printf("\n");
    for(i=0; i<soPT; i++)
    {
        printf("%3d ", i);
    }
    printf("\n");
    for(i=0; i<soPT; i++)
    {
        if(d[i] == VOCUC)
        {
            printf("%3s ", "-");
            continue;
        }
        printf("%3d ", d[i]);
    }
    printf("\n");
    for(i=0; i<soPT; i++)
    {
        printf("%3d ", parents[i]);
    }
    printf("\n\n\n");

}

void inNigekata(Graph graph, int v1, int v2, int *d, int *parents, int *soPT, char name[][100])
{
    int cuaVao = v1;
    int DcuaRa = VOCUC-1, cuaRa = cuaVao, key;
    int h, c, lap1, lap2;
    for(h=0; h < size; h++)
    {
        if(h == 0 || h == size-1)
        {
            for(c=0; c < size; c++)
            {
                if(tonTaiDiem(graph, h, c, name) == 0)
                {
                    continue;
                }
                key = convertIJtokey(h, c, name);
                if(key != cuaVao && d[key] < DcuaRa)
                {
                    cuaRa = key;
                    DcuaRa = d[key];
                }
            }
        }
        else
        {
            c = 0;
            {
                if(tonTaiDiem(graph, h, c, name) == 0)
                {
                    continue;
                }
                key = convertIJtokey(h, c, name);
                if(key != cuaVao && d[key] < DcuaRa)
                {
                    cuaRa = key;
                    DcuaRa = d[key];
                }
            }

            c = size - 1;
            {
                if(tonTaiDiem(graph, h, c, name) == 0)
                {
                    continue;
                }
                key = convertIJtokey(h, c, name);
                if(key != cuaVao && d[key] < DcuaRa)
                {
                    cuaRa = key;
                    DcuaRa = d[key];
                }
            }
        }
    }
    if(cuaRa == cuaVao)
    {
        printf("Tu %s khong the ra khoi me cung\n", convertItoA(cuaRa, name));
    }
    else
    {
        printf("Loi ra gan nhat: %s: ", convertItoA(cuaRa, name));
        InDuongDi(graph, cuaVao, cuaRa, d, parents, soPT, name);
    }
}

void InDuongDi(Graph graph, int v1, int v2, int *d, int *parents, int *soPT, char name[][100])
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

void dijkstra(Graph graph, int v1, int v2, void (* func)(Graph, int , int , int *, int *, int *, char *), char name[][100])
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
    func(graph, v1, v2, d, parents, soPT, name);
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


int tonTaiDiem(Graph graph, int h1, int c1, char name[][100])
{
    JRB node1, node2;
    char *array;
    int hang, cot;
    jrb_traverse(node1, graph.Vertex)
    {
        array = convertItoA(jval_i(node1->key), name);
        convertAtoIJ(array, &hang, &cot);
        if(hang == h1 && cot == c1)
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
    printf("n:%d; %s\n", n, name[n-1]);
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

void readFile(FILE *taptin, Graph graph, char name[][100])
{
    int bienChay1, key, soDinh = 0;int z;
    int giaTri[size][size], i, j;
    JRB node1;
    for(bienChay1 = 0;fscanf(taptin, "%d %d %d %d %d %d", &giaTri[bienChay1][0], &giaTri[bienChay1][1], &giaTri[bienChay1][2], &giaTri[bienChay1][3], &giaTri[bienChay1][4], &giaTri[bienChay1][5]) != EOF; bienChay1++)
    {
        //chay vong for nay chi de doc gia tri tu file
    }
    for(i = 0; i < bienChay1; i++)
    {
        for(j = 0; j < bienChay1; j++)
        {

            if(giaTri[i][j] == 0)
            {
                key = convertIJtokey(i, j, name);
                node1 = jrb_find_int(graph.Vertex, key);
                if(node1 == NULL)
                {
                    JRB node2 = make_jrb();
                    node1 = jrb_insert_int(graph.Vertex, key, new_jval_v(node2));
                    if(i-1 >= 0 && giaTri[i-1][j] == 0)
                    {
                        key = convertIJtokey(i-1, j, name);
                        node2 = jrb_find_int(graph.Vertex, key);
                        addEdge(graph, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(graph, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                    if(j-1 >= 0 && giaTri[i][j-1] == 0)
                    {
                        key = convertIJtokey(i, j-1, name);
                        node2 = jrb_find_int(graph.Vertex, key);
                        addEdge(graph, jval_i(node1->key), jval_i(node2->key), 1);
                        addEdge(graph, jval_i(node2->key), jval_i(node1->key), 1);
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
    addEgdeConLai(graph);
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
    cung /= 2;
    printf("%d nut, %d cung\n", nut, cung);
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
    int hang, cot;
    int MT[size][size];
    int bienChay1, bienChay2;
    JRB node1;
    for(bienChay1 = 0; bienChay1 < size; bienChay1++)
    {
        for(bienChay2 = 0; bienChay2 < size; bienChay2++)
        {
            MT[bienChay1][bienChay2] = 1;
        }
    }
    jrb_traverse(node1, graph.Egde)
    {
        convertAtoIJ(convertItoA(jval_i(node1->key), name), &hang, &cot);
        MT[hang][cot] = 0;
    }
    for(bienChay1 = 0; bienChay1 < size; bienChay1++)
    {
        for(bienChay2 = 0; bienChay2 < size; bienChay2++)
        {
            printf("%d ", MT[bienChay1][bienChay2]);
        }printf("\n");
    }
    printf("\n");
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


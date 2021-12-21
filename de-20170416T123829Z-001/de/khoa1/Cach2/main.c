#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define VOCUC 9999999

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
//int DFS(Graph graph, int v1, int v2, void (* func)(int));
//int BFS(Graph graph, int v1, int v2, void (* func)(int));
//void inVertex(int v);
//void dijkstra(Graph graph, int v1, int v2, void (* func)(int , int , int *, int *, int *));
int getTrongSo(Graph graph, int v1, int v2);//khong ton tai egde -> return 0
//void inThongTin(Graph graph);
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
    int luaChon, d1, d2, d3, d4, n, i, j, bienChay, max, tmp, key1, key2, daXet[20] = {};
    int *output = malloc(100*sizeof(int)), dinh[5][5];
    char name[20][100] = {};
    Graph graph = createGraph();
    FILE *taptin = fopen("input.txt", "r+");
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
                printf("Nhap 4 de: In diem co lien thong lon nhat\n");
                printf("Nhap 5 de: In ra danh sach cac nut dao\n");
                printf("Nhap 6 de: Tim duong di ngan nhat\n");
                printf("Nhap 7 de: In tong so cach di giua 2 diem bat ki\n");
                printf("Nhap 8 de: In do thi\n");
                printf("Nhap 9 de: Thoat chuong trinh\n");
                printf("Nhap de: ");
                scanf("%d", &luaChon);
                while(getchar() != '\n');
            }
            if(luaChon == 9)
            {
                fclose(taptin);
                exit(1);
            }
            else if(luaChon < 1 || luaChon > 9)
            {
                printf("Nhap cac so tu 1 -> 9\n");
                continue;
            }
            switch(luaChon)
            {
                case 1:
                {
                    //ham readFile o day, muon them vao case1 thi phai xoa readFile o tren kia di
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
                    scanf("%d", &d1);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &d2);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, d1, d2, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", d1, d2);
                        continue;
                    }

                    printf("Diem lien thong cua dinh %d%d: ", d1, d2);
                    inDiemLT(graph, d1, d2, funcPrint, name);
                    printf("\n");
                    break;
                }
                case 4:
                {
                    printf("Danh sach cac nut co lien thong lon nhat: ");
                    max = 0;
                    for(i=0; i<5; i++)
                    {
                        for(j=0; j<5; j++)
                        {
                            tmp = inDiemLT(graph, i, j, funcKhongPrint, name);
                            dinh[i][j] = tmp;
                            if(tmp > max)
                                max = tmp;
                        }
                    }
                    for(i=0; i<5; i++)
                    {
                        for(j=0; j<5; j++)
                        {
                            if(dinh[i][j] == max)
                                printf("%d%d ", i, j);
                        }
                    }
                    printf("\nLien thong lon nhat = %d\n", max);
                    break;
                }
                case 5:
                {
                    printf("Danh sach cac dao: ");
                    for(i=0; i<5; i++)
                    {
                        for(j=0; j<5; j++)
                        {
                            tmp = inDiemLT(graph, i, j, funcKhongPrint, name);
                            if(tmp == 0)
                            {
                                printf("%d%d ", i, j);
                            }
                        }
                    }
                    printf("\n");
                    break;
                }
                case 6:
                {
                    printf("Nhap diem xuat phat: \n");
                    printf("Hang: ");
                    scanf("%d", &d1);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &d2);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, d1, d2, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", d1, d2);
                        continue;
                    }

                    printf("Nhap diem dich: \n");
                    printf("Hang: ");
                    scanf("%d", &d3);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &d4);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, d3, d4, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", d3, d4);
                        continue;
                    }

                    key1 = convertIJtokey(d1, d2, name);
                    key2 = convertIJtokey(d3, d4, name);
                    dijkstra(graph, key1, key2, InDuongDi, name);
                    break;
                }
                case 7:
                {
                    for(i=0; i<20; i++)
                    {
                        daXet[i] = 0;
                    }
                    printf("Nhap diem xuat phat: \n");
                    printf("Hang: ");
                    scanf("%d", &d1);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &d2);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, d1, d2, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", d1, d2);
                        continue;
                    }

                    printf("Nhap diem dich: \n");
                    printf("Hang: ");
                    scanf("%d", &d3);
                    while(getchar() != '\n');
                    printf("Cot: ");
                    scanf("%d", &d4);
                    while(getchar() != '\n');
                    if(tonTaiDiem(graph, d3, d4, name) == 0)
                    {
                        printf("Dinh %d%d khong ton tai\n", d3, d4);
                        continue;
                    }

                    key1 = convertIJtokey(d1, d2, name);
                    key2 = convertIJtokey(d3, d4, name);
                    daXet[key1] = 1;
                    printf("Co %d cach di giua 2 diem %d%d-%d%d\n", cachDi(graph, key1, key2, name, daXet), d1, d2, d3, d4);


                    break;
                }
                case 8:
                {//printf("Nhap 11 de: In do thi\n");
                    /*printf("\n");
                    In(graph);*/
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

void readFile(FILE *taptin, Graph graph, char name[][100])
{
    int bienChay1, key, soDinh = 0;int z;
    int giaTri[5][5], i, j;
    JRB node1;
    for(bienChay1 = 0;fscanf(taptin, "%d %d %d %d %d", &giaTri[bienChay1][0], &giaTri[bienChay1][1], &giaTri[bienChay1][2], &giaTri[bienChay1][3], &giaTri[bienChay1][4]) != EOF; bienChay1++)
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
    int MT[5][5];
    int bienChay1, bienChay2;
    JRB node1;
    for(bienChay1 = 0; bienChay1 < 5; bienChay1++)
    {
        for(bienChay2 = 0; bienChay2 < 5; bienChay2++)
        {
            MT[bienChay1][bienChay2] = 1;
        }
    }
    jrb_traverse(node1, graph.Egde)
    {
        convertAtoIJ(convertItoA(jval_i(node1->key), name), &hang, &cot);
        MT[hang][cot] = 0;
    }
    for(bienChay1 = 0; bienChay1 < 5; bienChay1++)
    {
        for(bienChay2 = 0; bienChay2 < 5; bienChay2++)
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


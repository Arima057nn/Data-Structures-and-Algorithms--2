#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define VOCUC 1000
#define size 6

typedef struct Graph
{
    JRB Egde;
    JRB Vertex;
}Graph;

void YC1(FILE *taptin, Graph graph, char name[][100]);
void YC2(FILE *taptin, Graph graph, char name[][100]);
void YC3(FILE *taptin, Graph graph, char name[][100]);
void YC4(FILE *taptin, Graph graph, char name[][100]);
void YC5(FILE *taptin, Graph graph, char name[][100]);
void YC6(FILE *taptin, Graph graph, char name[][100]);

Graph createGraph();
void readFile(FILE *taptin, Graph graph, char name[][100]);
int convertAtoI(char *array, char name[][100]);
char *convertItoA(int key, char name[][100]);
void addVertex(Graph graph, int id, char* name);
void addEdge(Graph graph, int v1, int v2, int trongSo);
int hasEdge(Graph graph, int v1, int v2);
void addEgdeConLai(Graph graph);
void In(Graph graph, char name[][100]);
void inThongTin(Graph graph);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void topo(Graph graph);
char *getVertex(Graph graph, int id);
int getComponents(Graph graph, void (* func)(int));
int DFS(Graph graph, int v1, int v2, void (* func)(int));
void Kin();
int indegree_Sua(Graph graph, int v, int *output, int *daXet, int *n);
void DeQuy(Graph graph, int v, int *output, int daXet[], int *n);
void dijkstra_nguoc(Graph graph, int v1, int v2, void (* func)(Graph, int , int , int *, int *, int *, char *), char name[][100]);
void updateD(Graph graph, int v1, int v2, int *d, int *parents);
Dllist findQmax(Dllist queue, int *d);
void InDijkstr(Graph graph5, int v1, int v2, int *d, int *parents, int *soPT, char *name);
int getTrongSo(Graph graph, int v1, int v2);


int main()
{
    int luaChon;

    int *output = malloc(100*sizeof(int));
    char name[20][100] = {};
    Graph graph = createGraph();
    FILE *taptin = fopen("input.txt", "r+");
    JRB node1 = NULL, node2 = NULL;
    if(taptin != NULL)
    {

        YC1(taptin, graph, name);

        printf("\n");
        YC2(taptin, graph, name);

        printf("\n");
        YC3(taptin, graph, name);

        printf("\n");
        YC5(taptin, graph, name);

        printf("\n");
        YC6(taptin, graph, name);

        fclose(taptin);
    }
    else
    {
        printf("ERROR\n");
    }
    return 0;
}

void YC1(FILE *taptin, Graph graph, char name[][100])
{
    readFile(taptin, graph, name);
    In(graph, name);
    inThongTin(graph);

}

void YC2(FILE *taptin, Graph graph, char name[][100])
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
        n = indegree(graph, v, output);
        printf("So cong viec ngay truoc: %d\tLa cac cong viec: ", n);
        for(i1 = 0; i1 < n; i1++)
        {
            printf("%s ", convertItoA(output[i1], name));
        }
        printf("\n");
        n = 0;
        DeQuy(graph, v, output, daXet, &n);
        printf("Tong so cong viec truoc: %d\tLa: ", n);
        for(i1 = 0; i1 < n; i1++)
        {
            printf("%s ", convertItoA(output[i1], name));
        }
        printf("\n");

    }
    else
    {
        printf("Cong viec khong co trong chuong trinh\n");

    }
    free(output);
}

void YC3(FILE *taptin, Graph graph, char name[][100])
{
    char luaChon[10];
    printf("Co muon thuc hien lai yeu cau 2 nua khong? Y/N ");
    fgets(luaChon, 8, stdin);
    luaChon[strlen(luaChon) - 1] = '\0';
    printf("\n");
    while(1)
    {
        if(strcmp(luaChon, "Y") == 0 || strcmp(luaChon, "y") == 0)
        {
            YC2(taptin, graph, name);
            break;
        }
        else if(strcmp(luaChon, "N") == 0 || strcmp(luaChon, "n") == 0)
        {
            YC4(taptin, graph, name);
            break;
        }
    }
}

void YC4(FILE *taptin, Graph graph, char name[][100])
{
    printf("Thu tu truoc sau: ");
    topo(graph);
    printf("\n");
}

void YC5(FILE *taptin, Graph graph, char name[][100])
{
    int TF = 0, n, a1, b1;
    int *output = malloc(30*sizeof(int));
    int daXet[30] = {};
    char str[10];
    JRB node1, node2;
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
        Graph graph5 = createGraph();
        n = 0;
        DeQuy(graph, v, output, daXet, &n);
        //printf("Tong so cong viec truoc: %d\tLa: ", n);
        for(a1 = 0; a1 < n; a1++)
        {
            //printf("%s ", convertItoA(output[a1], name));
            jrb_insert_int(graph5.Vertex, output[a1], new_jval_s(getVertex(graph, output[a1])));

        }
        //them dinh v vao graph5 va output
        jrb_insert_int(graph5.Vertex, v, new_jval_s(getVertex(graph, v)));
        output[n] = v;
        n++;
        addEgdeConLai(graph5);
        printf("\n");
       /* jrb_traverse(node1, graph5.Vertex)
        {
            printf("Dinh %s(%d):", convertItoA(jval_i(node1->key), name), jval_i(node1->key));
            printf("\n");
        }
*/
        for(a1 = 0; a1 < n; a1++)
        {
            for(b1 = a1; b1 < n; b1++)
            {

                if(output[a1] != output[b1])
                {
                    //printf("has: %d->%d?\ti: %d, j: %d\n", output[a1], output[b1], a1, b1);
                    if(hasEdge(graph, output[a1], output[b1]))
                    {
                        //printf("\thas: %d->%d\n", output[a1], output[b1]);
                        addEdge(graph5, output[b1], output[a1] , getTrongSo(graph, output[a1], output[b1]));//add canh nguoc voi graph
                    }
                    if(hasEdge(graph, output[b1], output[a1]))
                    {
                     //printf("\thas: %d->%d\n", output[b1], output[a1]);
                        addEdge(graph5, output[a1], output[b1] , getTrongSo(graph, output[b1], output[a1]));//add canh nguoc voi graph
                    }
                }

            }
        }

        dijkstra_nguoc(graph5, v, -1, InDijkstr, name);
    }
    else
    {
        printf("Cong viec khong co trong chuong trinh\n");

    }
    free(output);
}


void YC6(FILE *taptin, Graph graph, char name[][100])
{
    if(getComponents(graph, Kin))
    {
        printf("\nDo thi co chu trinh\n");
    }
    else
        printf("\nDo thi khong co chu trinh\n");

}

void InDijkstr(Graph graph, int v1, int v2, int *d, int *parents, int *soPT, char *name)
{
    /*int i;
    printf("\n");
    for(i = 0; i < soPT; i++)
    {
        printf("%3d ", i);
    }
    printf("\n");
    for(i = 0; i < soPT; i++)
    {
        printf("%3d ", d[i]);
    }
    printf("\n");
    for(i = 0; i < soPT; i++)
    {
        printf("%3d ", parents[i]);
    }
    printf("\n\n\n");*/


    JRB node1, node2;
    int *output = malloc(sizeof(int) * 20);
    int Dmax = 0;
    jrb_traverse(node1, graph.Egde)
    {
        if(outdegree(graph, jval_i(node1->key), output) == 0 && Dmax < d[jval_i(node1->key)])
        {
            Dmax = d[jval_i(node1->key)];
        }
    }
    printf("Thoi gian toi thieu de hoan thanh %s la: %d\n", convertItoA(v1, name), Dmax);
    free(output);
}


void dijkstra_nguoc(Graph graph, int v1, int v2, void (* func)(Graph, int , int , int *, int *, int *, char *), char name[][100])
{
    int soPT = 0, i;
    int d[20] = {};
    int parents[20] = {};
    for(i=0; i<20; i++)
    {
        d[i] = 0;
        parents[i] = -1;
    }
    d[v1] = VOCUC;
    parents[v1] = v1;
    Dllist queue = new_dllist(), Qnode = NULL, Qmax = NULL;
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Vertex)
    {
        dll_append(queue, node1->key);
        soPT++;
    }
    while(!dll_empty(queue))
    {
        Qmax = findQmax(queue, d);
        node1 = jrb_find_int(graph.Egde, jval_i(Qmax->val));

        //phai kiem tra xem d[jval_i(Qmax->val)] co phai la max chua (them 1 buoc so voi dijkstra)
        int *output = malloc(sizeof(int) * 20);
        int n = indegree(graph, jval_i(Qmax->val), output), i1;
        if(jval_i(Qmax->val) != v1)
        {
            for(i1 = 0; i1 < n; i1++)
            {
                updateD(graph, output[i1], jval_i(Qmax->val), d, parents);
            }
        }

        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            updateD(graph, jval_i(Qmax->val), jval_i(node2->key), d, parents);
        }
        dll_delete_node(Qmax);
    }
    for(i=0; i<20; i++)
    {
        d[i] -= VOCUC;
    }
    func(graph, v1, v2, d, parents, soPT, name);
}



Dllist findQmax(Dllist queue, int *d)
{
    Dllist Qnode = NULL, Qmax = NULL;
    Qnode = dll_first(queue);
    Qmax = Qnode;
    for(; Qnode != dll_last(queue); )
    {
        if(d[jval_i(Qnode->val)] > d[jval_i(Qmax->val)])
        {
            Qmax = Qnode;
        }
        Qnode = dll_next(Qnode);
    }
    Qnode = dll_next(Qnode);
    Qnode = dll_last(queue);//vong while khong den duoc node cuoi
    if(d[jval_i(Qnode->val)] > d[jval_i(Qmax->val)])
    {
        Qmax = Qnode;
    }
    return Qmax;
}



void updateD(Graph graph, int v1, int v2, int *d, int *parents)
{
    if(d[v2] < (d[v1] + getTrongSo(graph, v1, v2)))
    {
        //int old = d[v2];
        d[v2] = d[v1] + getTrongSo(graph, v1, v2);
        //printf("%d->%d; old: %d; new: %d\n", v1, v2, old, d[v2]);
        parents[v2] = v1;
    }
}

void Kin()//khong in
{

}

int getComponents(Graph graph, void (* func)(int))//kiem tra xem co chu trinh hay k
{
    int i = 0, n;
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Vertex)
    {
        if(DFS(graph, jval_i(node1->key), -1, func) == -1)//khong in
        {
            return 1;
        }
    }
    return 0;
}

int DFS(Graph graph, int v1, int v2, void (* func)(int))//neu co TH v2 == v1 thi return -1
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
        func(d1);
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

void topo(Graph graph)
/*Sap xep topo la: neu co canh u->v thi phai in ra u truoc v; do thi phai khong co chu trinh
Thuat toan:
    -Duyet qua do thi, nem cac dinh co indegree = 0 vao queue, ghi lai degree cua cac dinh vao 1 mang
    -Lay 1 dinh trong queue ra, duyet danh sach ke cua no, giam degree cua cac dinh ke di 1, neu dinh nao degree = 0
        thi them vao queue
    -Lap lai den khi queue rong
    -Ham in ra thu tu cac dinh sap xep theo kieu topo
*/
{
    Dllist queue = new_dllist(), Qnode;
    JRB node1, node2;
    int *output = malloc(100* sizeof(int));//tao ra chu ham topo khong can dung//khong xoa
    int banBacVao[100], bbv;
    jrb_traverse(node1, graph.Vertex)
    {
        bbv = indegree(graph, jval_i(node1->key), output);
        banBacVao[jval_i(node1->key)] = bbv;
        if(bbv == 0)
        {
            dll_append(queue, node1->key);
        }
    }
    int test;
    while(!dll_empty(queue))
    {
        Qnode = dll_first(queue);
        printf("%s ", getVertex(graph, jval_i(Qnode->val)));
        node1 = jrb_find_int(graph.Egde, jval_i(Qnode->val));
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            banBacVao[jval_i(node2->key)]--;
            if(banBacVao[jval_i(node2->key)] == 0)
            {
                 dll_append(queue, node2->key);
            }
        }
        dll_delete_node(Qnode);
    }
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
        printf("Dinh %s:", convertItoA(jval_i(node1->key), name));
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            printf("  %s(%d)", convertItoA(jval_i(node2->key), name), getTrongSo(graph, jval_i(node1->key), jval_i(node2->key)));
        }
        printf("\n");
    }
}

void readFile(FILE *taptin, Graph graph, char name[][100])
{
    int i1, key, time;
    char hangDangDoc[100], *ViTri, *Ptr, *tenCV;
    while(fgets(hangDangDoc, 100, taptin) != NULL)
    {
        hangDangDoc[strlen(hangDangDoc) - 1] = '\0';
        ViTri = hangDangDoc;

        Ptr = strstr(ViTri, " ");// tim ' ' truoc ':'
        *Ptr = '\0';// tu ViTri->Ptr la ten cong viec A
        //printf("%s\n", ViTri);
        key = convertAtoI(ViTri, name);
        addVertex(graph, key, strdup(ViTri));

        ViTri = ++Ptr;// de ViTri va Ptr nhay qua ki tu '\0' ('\0' o truoc ':')
        while((ViTri = strstr(ViTri, "A")) && (ViTri != NULL))
        {
            Ptr = strstr(ViTri, "-");
            *Ptr = '\0';// tu ViTri->Ptr la ten cong viec B
            tenCV = ViTri;

            ViTri = Ptr+1;
            Ptr = strstr(ViTri, " ");// neu k tim duoc thi tu ViTri->het dong la time cong viec B
            if(Ptr != NULL)// neu tim duoc thi tu ViTri->Ptr la time cong viec B
            {
                *Ptr = '\0';
                addEdge(graph, convertAtoI(tenCV, name), key, atoi(ViTri));
                ViTri = ++Ptr;// de ViTri va Ptr nhay qua ki tu '\0' ('\0' thay boi dau ' ' giua 2 cong viec B, C)
            }
            else
            {
                addEdge(graph, convertAtoI(tenCV, name), key, atoi(ViTri));
            }
        }
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



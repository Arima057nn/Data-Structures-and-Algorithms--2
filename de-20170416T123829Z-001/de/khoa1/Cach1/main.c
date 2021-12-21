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
void In(Graph graph);
void addEgdeConLai(Graph graph);
//int DFS(Graph graph, int v1, int v2, void (* func)(int));
//int BFS(Graph graph, int v1, int v2, void (* func)(int));
//void inVertex(int v);
//void dijkstra(Graph graph, int v1, int v2, void (* func)(int , int , int *, int *, int *));
//int getTrongSo(Graph graph, int v1, int v2);//khong ton tai egde -> return 0
void inThongTin(Graph graph);
int inDiemLT(Graph graph, int hang, int cot, void (*func)(int, int));
void funcPrint(int hang, int cot);
void funcKhongPrint(int hang, int cot);
int tonTaiDiem(Graph graph, int d1, int d2);

int tonTaiDiem(Graph graph, int d1, int d2)
{
    JRB node1, node2;
    node1 = jrb_find_int(graph.Egde, d1);
    if(node1 == NULL)
    {
        return 0;
    }
    else
    {
        node2 = jrb_find_int(((JRB)jval_v(node1->val)), d2);
        if(node2 == NULL)
        {
            return 0;
        }
    }
    return 1;
}

void funcPrint(int hang, int cot)
{
    printf("%d%d\n", hang, cot);
}

void funcKhongPrint(int hang, int cot)
{

}

int inDiemLT(Graph graph, int hang, int cot, void (*func)(int, int))
{
    if(tonTaiDiem(graph, hang, cot) == 0)
    {
        return -1;
    }
    int bienChay1, bienChay2, n, diemLT = 0;
    int *output = malloc(10*sizeof(int));
    n = outdegree(graph, hang, output);
    for(bienChay1 = 0; bienChay1 < n; bienChay1++)
    {
        if((output[bienChay1] == cot+1) || (output[bienChay1] == cot-1))
        {
            //printf("%d%d\n", hang, output[bienChay1]);
            func(hang, output[bienChay1]);
            diemLT++;
        }
    }

    n = indegree(graph, cot, output);
    for(bienChay1 = 0; bienChay1 < n; bienChay1++)
    {
        if((output[bienChay1] == hang+1) || (output[bienChay1] == hang-1))
        {
            //printf("%d%d\n", output[bienChay1], cot);
            func(output[bienChay1], cot);
            diemLT++;
        }
    }
    free(output);
    return diemLT;
}

int main()
{
    int luaChon, d1, d2, n, i, j, bienChay, max, tmp;
    int *output = malloc(100*sizeof(int)), dinh[5][5];
    Graph graph = createGraph();
    FILE *taptin = fopen("input.txt", "r+");
    JRB node1 = NULL, node2 = NULL;
    if(taptin != NULL)
    {

        readFile(taptin, graph);
        while(1)
        {
            {//menu
                printf("\nNhap 1 de: Doc file va in ma tran\n");
                printf("Nhap 2 de: In so nut va so cung\n");
                printf("Nhap 3 de: In ra diem lien thong\n");
                printf("Nhap 4 de: In diem co lien thong lon nhat\n");
                printf("Nhap 5 de: In ra danh sach cac nut dao\n");
                printf("Nhap 6 de: Tim duong di ngan nhat\n");
                printf("Nhap 7 de: In tong so cach di tu 2 diem bat ki\n");
                printf("Nhap 8 de: In do thi\n");
                printf("Nhap 9 de: Thoat chuong trinh\n");
                printf("Nhap de: ");
                scanf("%d", &luaChon);
                while(getchar() != '\n');
            }
            if(luaChon == 9)
            {
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
                    if(tonTaiDiem(graph, d1, d2) == 0)
                    {
                        printf("Dinh khong ton tai\n");
                        continue;
                    }

                    printf("Diem lien thong cua dinh %d%d: \n", d1, d2);
                    inDiemLT(graph, d1, d2, funcPrint);
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
                            tmp = inDiemLT(graph, i, j, funcKhongPrint);
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
                            tmp = inDiemLT(graph, i, j, funcKhongPrint);
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
                    printf("Cai dat jrb dang nay k lam dc, xem cach 2\n");
                    break;
                }
                case 7:
                {
                    printf("Cai dat jrb dang nay k lam dc, xem cach 2\n");
                    break;
                }
                case 8:
                {//printf("Nhap 11 de: In do thi\n");
                    printf("\n");
                    In(graph);
                    break;
                }

            }
        }

    }
    else
    {
        printf("ERROR\n");
    }
    return 0;
}

void readFile(FILE *taptin, Graph graph)
{
    int bienChay1;
    int giaTri[5][5], i, j;
    for(bienChay1 = 0;fscanf(taptin, "%d %d %d %d %d", &giaTri[bienChay1][0], &giaTri[bienChay1][1], &giaTri[bienChay1][2], &giaTri[bienChay1][3], &giaTri[bienChay1][4]) != EOF; bienChay1++)
    {
        //chay vong for nay chi de doc gia tri tu file
    }
    for(i = 0; i < bienChay1; i++)//add 5 dinh
    {
        addVertex(graph, i, "");
    }
    for(i = 0; i < bienChay1; i++)//add canh
    {
        for(j = 0; j < bienChay1; j++)
        {
            //if(i != j && giaTri[i][j] == 0)
            if(giaTri[i][j] == 0)
            {
                printf("Them canh %d->%d\n", i, j);
                addEdge(graph, i, j, 1);
                //printf("Them canh %d->%d\n\n", j, i);
                //addEdge(graph, j, i, 1);
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
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            nut++;
            if(jval_i(node1->key) != jval_i(node2->key))
            {
                cung++;
            }
        }
    }
    printf("%d nut, %d cung\n", nut, cung);
}


/*
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
}*/
/*
void updateD(Graph graph, Dllist Qmin, JRB node2, int *d, int *parents)
{
    //printf("Xet %d: d: %d; new: %d\n", jval_i(node2->key), d[jval_i(node2->key)], (d[jval_i(Qmin->val)] + getTrongSo(graph, jval_i(Qmin->val), jval_i(node2->key))));
    if(d[jval_i(node2->key)] > (d[jval_i(Qmin->val)] + getTrongSo(graph, jval_i(Qmin->val), jval_i(node2->key))))
    {
        d[jval_i(node2->key)] = d[jval_i(Qmin->val)] + getTrongSo(graph, jval_i(Qmin->val), jval_i(node2->key));
        parents[jval_i(node2->key)] = jval_i(Qmin->val);
    }

}*/
/*
InDijkstr(int v1, int v2, int *d, int *parents, int *soPT)//khogn can dung v2
{
    int i;
    printf("\n");
    for(i=1; i<=soPT; i++)
    {
        printf("%3d ", i);
    }
    printf("\n");
    for(i=1; i<=soPT; i++)
    {
        printf("%3d ", d[i]);
    }
    printf("\n");
    for(i=1; i<=soPT; i++)
    {
        printf("%3d ", parents[i]);
    }
    printf("\n\n\n");

}*/
/*
void InDuongDi(int v1, int v2, int *d, int *parents, int *soPT)
{
    int v = v2, bienChay;
    int duongDi[20] = {}, n=0;
    printf("\nDuong di ngan nhat tu %d->%d: ", v1, v2);
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

        printf("%d ", duongDi[bienChay]);

    }
    printf("\n\n");
}*/
/*
void dijkstra(Graph graph, int v1, int v2, void (* func)(int , int , int *, int *, int *))
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
    func(v1, v2, d, parents, soPT);
}*/
/*
void func(int z)
{
    printf("%d ", z);
}
*/

/*
void Kin()//khong in
{

}
*/
/*
int getComponents(Graph graph, void (* func)(int))//kiem tra xem co chu trinh hay k
{
    int i = 0, n;
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Vertex)
    {
        if(DFS(graph, jval_i(node1->key), -1, Kin) == -1)//khong in
        {
            return 1;
        }
    }
    return 0;
}*/

/*
void inVertex(int v)
{
    printf("%d ", v);
}*/
/*
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

*/
/*
int BFS(Graph graph, int v1, int v2, void (* func)(int))
{
    if(jrb_find_int(graph.Vertex, v1) == NULL)
    {
        printf("Khong ton tai dinh %d\n", v1);
        return 0;
    }
    int daXet[20] = {}, d1;
    daXet[v1] = 1;
    Dllist queue = new_dllist(), Qnode = NULL;
    JRB node1 = NULL, node2 = NULL;
    dll_append(queue, new_jval_i(v1));
    while(!dll_empty(queue))
    {
        Qnode = dll_first(queue);
        d1 = jval_i(Qnode->val);
        func(d1);
        dll_delete_node(Qnode);
        if(d1 == v2)
        {
            free_dllist(queue);
            return 1;
        }
        node1 = jrb_find_int(graph.Egde, d1);
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            if(daXet[jval_i(node2->key)] == 0)
            {
                dll_append(queue, node2->key);
                daXet[jval_i(node2->key)] = 1;
            }
        }
    }
    free_dllist(queue);
    return 1;
}

*/

//void topo(Graph graph)
/*Sap xep topo la: neu co canh u->v thi phai in ra u truoc v; do thi phai khong co chu trinh
Thuat toan:
    -Duyet qua do thi, nem cac dinh co indegree = 0 vao queue, ghi lai degree cua cac dinh vao 1 mang
    -Lay 1 dinh trong queue ra, duyet danh sach ke cua no, giam degree cua cac dinh ke di 1, neu dinh nao degree = 0
        thi them vao queue
    -Lap lai den khi queue rong
    -Ham in ra thu tu cac dinh sap xep theo kieu topo
*/
/*{
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
        printf("%d(%s) ", jval_i(Qnode->val), getVertex(graph, jval_i(Qnode->val)));
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
*/



/*
void dropGraph(Graph graph)
{
    JRB node1 = NULL;
    jrb_traverse(node1, graph.Egde)
    {
        free(node1);
    }
    free(graph.Egde);

    jrb_traverse(node1, graph.Vertex)
    {
        free(node1);
    }
    free(graph.Vertex);
}

*/


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


/*
void hasEdge(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph.Egde, v1);
    if(node == NULL)
    {
        printf("Khong co canh %d -> %d\n", v1, v2);
    }
    else
    {
        JRB node2 = jrb_find_int((JRB)jval_v(node->val), v2);
        if(node2 == NULL)
        {
            printf("Khong co canh %d -> %d\n", v1, v2);
        }
        else
        {
            printf("Co canh %d -> %d\n", v1, v2);
        }
    }
}
*/


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
*/

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

void In(Graph graph)
{
    JRB node1 = NULL, node2 = NULL;
    jrb_traverse(node1, graph.Egde)
    {
        printf("Dinh %d:", jval_i(node1->key));
        jrb_traverse(node2, ((JRB)jval_v(node1->val)))
        {
            printf("  %d", jval_i(node2->key));
        }
        printf("\n");
    }
}




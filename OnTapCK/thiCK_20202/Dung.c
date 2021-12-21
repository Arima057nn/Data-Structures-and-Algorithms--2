#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
#include "string.h"

#define INFINITIVE_VALUE 10000000

typedef struct
{
    JRB vertices;
    JRB edges;
} Graph;

Graph createGraph();
void addVertex(Graph g, int id, char *name);
void addEdge(Graph g, int v1, int v2, double weight);

char *getVertexName(Graph g, int id);
int getVertexId(Graph g, char *name);
double getEdgeValue(Graph g, int v1, int v2);
int hasEdge(Graph g, int v1, int v2);

Dllist incomingVertices(Graph g, int v);
Dllist outgoingVertices(Graph g, int v);

int indegree(Graph graph, int v);
int outdegree(Graph graph, int v);

void dropGraph(Graph g);

void printfVertex(int v);
void BFS(Graph g, int source, int dest, void (*f)(int key));
void DFS(Graph g, int source, int dest, void (*f)(int key));
int isDAG(Graph g);
Dllist dll_min(Dllist list, JRB cost, JRB visited);
Dllist findPath(JRB parent, int source, int dest);
double shortestPath(Graph g, int source, int dest);

int readFile1(Graph g, FILE *ptr, JRB SDT, JRB NAME)
{
    int n, ID = 1;
    char cccd[13], sdt[11], name[30];
    fscanf(ptr, "%d%*c", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(ptr, "%s%s%s%*c", cccd, sdt, name);
        addVertex(g, ID, cccd);
        ID++;
        // printf("%s %s", name, sdt);
        jrb_insert_str(SDT, strdup(cccd), new_jval_s(sdt));
        jrb_insert_str(NAME, strdup(cccd), new_jval_s(name));
    }

    return ID;
}

int readFile2(Graph g, FILE *fptr)
{
    int m;
    char cccd1[13], cccd2[13];
    double time;
    fscanf(fptr, "%d%*c", &m);
    for (int i = 0; i < m; i++)
    {
        fscanf(fptr, "%s%s%lf%*c", cccd1, cccd2, &time);

        addEdge(g, getVertexId(g, cccd1), getVertexId(g, cccd2), time);
    }
    return m;
}
void CapNhatTG(Graph g, int v1, int v2, double time)
{
    JRB p, node1, node2;
    node1 = jrb_find_int(g.edges, v1);
    p = jrb_find_int((JRB)(jval_v(node1->val)), v2);
    p->val = new_jval_d(time);

    node2 = jrb_find_int(g.edges, v2);
    p = jrb_find_int((JRB)(jval_v(node2->val)), v1);
    p->val = new_jval_d(time);
}
int main()
{
    FILE *ptr, *fptr;
    Dllist node, List;
    JRB p, SDT = make_jrb(), NAME = make_jrb();
    Graph g = createGraph();
    int choose, i, n, m, ID;
    double time, c;
    char cccd[13], sdt[11], name[30], cccd1[13], cccd2[13];
    while (1)
    {
        printf("\n======= MENU =======\n"
               "1.Doc du lieu\n"
               "2.Dang ki mot cong dan moi\n"
               "3.Ghi nhan tiep xuc\n"
               "4.Tra cuu cong dan\n"
               "5.Tra cuu thong tin tiep xuc\n"
               "6.Tra cuu mang luoi tiep xuc\n"
               "7.Ket thuc chuong trinh\n"
               "--->Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            ptr = fopen("DANCU.txt", "r");
            fptr = fopen("TIEPXUC.txt", "r");
            ID = readFile1(g, ptr, SDT, NAME);
            m = readFile2(g, fptr);
            printf("Tong so dinh: %d\n", ID - 1);
            printf("Tong so canh: %d\n", m);
            fclose(ptr);
            fclose(fptr);
            printf("\n");
            break;
        case 2:
            printf("Nhap CCCD: ");
            c = getchar();
            gets(cccd);
            if (getVertexId(g, cccd) == -1)
            {
                printf("--> Them cong dan!\n");
                printf("-Nhap SDT: ");
                // c = getchar();
                gets(sdt);
                printf("\n-Nhap Ho ten: ");
                // c = getchar();
                gets(name);
                addVertex(g, ID, cccd);
                jrb_insert_str(SDT, strdup(cccd), new_jval_s(strdup(sdt)));
                jrb_insert_str(NAME, strdup(cccd), new_jval_s(strdup(name)));
                ID++;
                printf("So ban ghi cong dan sau khi cap nhat la: %d\n", ID - 1);
            }
            else
            {
                printf("Cap nhat thong tin!");
                printf("-Nhap SDT: ");
                // c = getchar();
                gets(sdt);
                printf("\n-Nhap Ho ten: ");
                // c = getchar();
                gets(name);
                p = jrb_find_str(NAME, strdup(cccd));
                jrb_delete_node(p);
                jrb_insert_str(NAME, strdup(cccd), new_jval_s(strdup(name)));
                p = jrb_find_str(SDT, strdup(cccd));
                jrb_delete_node(p);
                jrb_insert_str(SDT, strdup(cccd), new_jval_s(strdup(sdt)));
                printf("So ban ghi cong dan sau khi cap nhat la: %d\n", ID - 1);
            }

            //printf("%s %s %s", cccd, sdt, name);

            // jrb_traverse(p, g.edges)
            // {
            //     printf("%d", jval_i(p->key));
            // }
            printf("\n");
            break;
        case 3:
            do
            {
                printf("Nhap cccd nguoi 1: ");
                scanf("%s%*c", cccd1);
                // printf("%s\n", cccd1);
            } while (getVertexId(g, cccd1) == -1);
            do
            {
                printf("Nhap cccd nguoi 2: ");
                scanf("%s%*c", cccd2);
                // printf("%s\n", cccd2);
            } while (getVertexId(g, cccd2) == -1);
            if (hasEdge(g, getVertexId(g, cccd1), getVertexId(g, cccd2)) == 0)
            {
                printf("Nhap ngay tiep xuc: ");
                scanf("%lf", &time);
                printf("Them tiep xuc!\n");
                addEdge(g, getVertexId(g, cccd1), getVertexId(g, cccd2), time);
                m++;
                printf("Tong so tiep xuc sau cap nhat la: %d\n", m);
            }
            else
            {
                printf("Nhap ngay tiep xuc: ");
                scanf("%lf", &time);
                CapNhatTG(g, getVertexId(g, cccd1), getVertexId(g, cccd2), time);
                printf("Tong so tiep xuc sau cap nhat la: %d\n", m);
            }

            break;
        case 4:

            printf("Nhap CCCD: ");
            scanf("%s%*c", cccd);
            if (getVertexId(g, cccd) == -1)
            {
                printf("--> Khong ton tai!\n");
            }
            else
            {
                p = jrb_find_str(NAME, cccd);
                printf("Ho Ten: %s\n", jval_s(p->val));
                p = jrb_find_str(SDT, cccd);
                printf("SDT: %s", jval_s(p->val));
            }
            printf("\n");
            break;
        case 5:
            printf("Nhap CCCD: ");
            scanf("%s%*c", cccd);
            printf("\n");

            if (getVertexId(g, cccd) == -1)
            {
                printf("Khong tin tai!\n");
            }
            printf("%d", getVertexId(g, cccd));
            if (getVertexId(g, cccd) != -1)
            {
                List = outgoingVertices(g, getVertexId(g, cccd));

                if (List == NULL)
                {
                    printf("Khong co tiep xuc!\n");
                }
                else
                {
                    dll_traverse(node, List)
                    {
                        printf("%-20s \n", jval_s(dll_val(node)));
                    }
                }
            }
            break;
        case 6:
            printf("Nhap CCCD: ");
            scanf("%s%*c", cccd);
            printf("\n");
            if (getVertexId(g, cccd) == -1)
            {
                printf("Khong tin tai!\n");
            }
            break;
        case 7:
            dropGraph(g);
            exit(0);
            break;
        }
    }

    return 0;
}

Graph createGraph() // Tao mot cay
{
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

void addVertex(Graph g, int id, char *name) // Them dinh
{
    JRB node = jrb_find_int(g.vertices, id);

    if (node == NULL)
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

void addEdge(Graph g, int v1, int v2, double weight) // Them canh
{
    JRB node, l;

    node = jrb_find_int(g.edges, v1);
    if (node != NULL)
    {
        l = (JRB)jval_v(node->val);
        jrb_insert_int(l, v2, new_jval_i(weight));
    }
    else
    {
        l = make_jrb();
        jrb_insert_int(l, v2, new_jval_i(weight));
        jrb_insert_int(g.edges, v1, new_jval_v(l));
    }

    node = jrb_find_int(g.edges, v2);
    if (node != NULL)
    {
        l = (JRB)jval_v(node->val);
        jrb_insert_int(l, v1, new_jval_i(weight));
    }
    else
    {
        l = make_jrb();
        jrb_insert_int(l, v1, new_jval_i(weight));
        jrb_insert_int(g.edges, v2, new_jval_v(l));
    }
}

char *getVertexName(Graph g, int id) // tim kiem theo id
{
    JRB node = jrb_find_int(g.vertices, id);

    if (node != NULL)
        return jval_s(node->val);
    else
        return NULL;
}

int getVertexId(Graph g, char *name) // tim kiem theo ten
{
    JRB i;

    jrb_traverse(i, g.vertices)
    {
        if (strcmp(name, jval_s(i->val)) == 0)
            return jval_i(i->key);
    }
    return -1;
}

double getEdgeValue(Graph g, int v1, int v2) // kiem tra do dai khoang cach
{
    JRB node, l;

    if ((node = jrb_find_int(g.edges, v1)) != NULL)
    {
        if ((l = jrb_find_int((JRB)(jval_v(node->val)), v2)) != NULL)
            return jval_i(l->val);
        else
            return -1;
    }
    else
        return -1;
}

int hasEdge(Graph g, int v1, int v2) //kiem tra co duong di di giua 2 dinh
{
    JRB node;

    if ((node = jrb_find_int(g.edges, v1)) != NULL)
    {
        if (jrb_find_int((JRB)(jval_v(node->val)), v2) != NULL)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int indegree(Graph graph, int v)
{
    JRB tree, node;
    int output[50];
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

int outdegree(Graph graph, int v)
{
    JRB tree, node;
    int output[50];
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}
Dllist outgoingVertices(Graph g, int v) //cac
{
    JRB node, l, i;
    Dllist output = new_dllist();

    if ((node = jrb_find_int(g.edges, v)) == NULL)
        return output;

    l = (JRB)jval_v(node->val);
    jrb_traverse(i, l)
    {
        dll_append(output, i->key);
    }
    return output;
}

Dllist incomingVertices(Graph g, int v)
{
    JRB node, l, i;
    Dllist output = new_dllist();

    jrb_traverse(node, g.edges)
    {
        l = (JRB)jval_v(node->val);
        if (jrb_find_int(l, v) != NULL)
            dll_append(output, node->key);
    }
    return output;
}
void dropGraph(Graph g)
{
    JRB i;

    jrb_traverse(i, g.vertices)
    {
        free(jval_v(i->val));
    }
    jrb_free_tree(g.vertices);

    jrb_traverse(i, g.edges)
        jrb_free_tree((JRB)jval_v(i->val));
    jrb_free_tree(g.edges);
}

void printfVertex(int v)
{
    printf("%4d", v);
}

void BFS(Graph g, int source, int dest, void (*f)(int key))
{
    JRB visited = make_jrb();
    Dllist q = new_dllist();
    Dllist n;
    Dllist adjs;
    int i, u;

    dll_append(q, new_jval_i(source));
    while (!dll_empty(q))
    {
        n = dll_first(q);
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (jrb_find_int(visited, u) == NULL)
        {
            f(u);
            jrb_insert_int(visited, u, new_jval_i(1));
            adjs = outgoingVertices(g, u);

            dll_traverse(n, adjs)
            {
                if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
                    dll_append(q, dll_val(n));
                if (jval_i(dll_val(n)) == dest)
                {
                    free_dllist(adjs);
                    jrb_free_tree(visited);
                    free_dllist(q);
                    return;
                }
            }
            free_dllist(adjs);
        }
    }
    jrb_free_tree(visited);
    free_dllist(q);
}

void DFS(Graph g, int source, int dest, void (*f)(int key))
{
    JRB visited = make_jrb();
    Dllist q = new_dllist();
    Dllist n;
    Dllist adjs;
    int i, u;

    dll_append(q, new_jval_i(source));
    while (!dll_empty(q))
    {
        n = dll_last(q);
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (jrb_find_int(visited, u) == NULL)
        {
            f(u);
            jrb_insert_int(visited, u, new_jval_i(1));
            adjs = outgoingVertices(g, u);

            dll_rtraverse(n, adjs)
            {
                if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
                    dll_append(q, dll_val(n));
                if (jval_i(dll_val(n)) == dest)
                {
                    free_dllist(adjs);
                    jrb_free_tree(visited);
                    free_dllist(q);
                    return;
                }
            }
            free_dllist(adjs);
        }
    }
    jrb_free_tree(visited);
    free_dllist(q);
}

int onCycle(Graph g, int v)
{
    JRB visited = make_jrb();
    Dllist q = new_dllist();
    Dllist n;
    Dllist adjs;
    int i, u;

    dll_append(q, new_jval_i(v));
    while (!dll_empty(q))
    {
        n = dll_first(q);
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (jrb_find_int(visited, u) == NULL)
        {
            jrb_insert_int(visited, u, new_jval_i(1));
            adjs = outgoingVertices(g, u);

            dll_rtraverse(n, adjs)
            {
                if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
                    dll_append(q, dll_val(n));
                if (hasEdge(g, jval_i(dll_val(n)), v))
                {
                    free_dllist(adjs);
                    jrb_free_tree(visited);
                    free_dllist(q);
                    return 1;
                }
            }
            free_dllist(adjs);
        }
    }
    jrb_free_tree(visited);
    free_dllist(q);
    return 0;
}

int isDAG(Graph g)
{
    JRB node;
    jrb_traverse(node, g.vertices)
    {
        if (onCycle(g, jval_i(node->key)))
            return 0;
    }
    return 1;
}

Dllist dll_min(Dllist list, JRB cost, JRB visited)
{
    Dllist node;
    JRB node_g, node_m;
    int min = INFINITIVE_VALUE;
    jrb_traverse(node_g, cost)
    {
        if (jval_i(node_g->val) < min && jrb_find_int(visited, jval_i(node_g->key)) == NULL)
        {
            min = jval_i(node_g->val);
            node_m = node_g;
        }
    }
    dll_traverse(node, list)
    {
        if (jval_i(dll_val(node)) == jval_i(node_m->key))
            return node;
    }
    if (min == INFINITIVE_VALUE)
        return NULL;
}

Dllist findPath(JRB parent, int source, int dest)
{
    JRB node = jrb_find_int(parent, dest);
    Dllist path = new_dllist();
    dll_prepend(path, new_jval_i(dest));
    while (jval_i(node->val) != source)
    {
        dll_prepend(path, node->val);
        node = jrb_find_int(parent, jval_i(node->val));
    }
    dll_prepend(path, new_jval_i(source));
    return path;
}

double shortestPath(Graph g, int source, int dest)
{
    JRB visited = make_jrb();
    JRB cost = make_jrb();
    JRB parent = make_jrb();
    JRB node;
    Dllist q = new_dllist();
    Dllist path;
    Dllist n;
    Dllist adjs;
    int i, u, k;
    dll_append(q, new_jval_i(source));
    jrb_traverse(node, g.vertices)
    {
        jrb_insert_int(cost, jval_i(node->key), new_jval_i(INFINITIVE_VALUE));
    }
    jrb_find_int(cost, source)->val = new_jval_i(0);
    while (1)
    {
        n = dll_min(q, cost, visited);
        if (n == NULL)
        {
            printf("ROUTE NOT FOUND\n");
            jrb_free_tree(visited);
            jrb_free_tree(cost);
            jrb_free_tree(parent);
            free_dllist(q);
            return u;
        }
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (u == dest)
            break;

        k = jval_i(jrb_find_int(cost, u)->val); //gia tri cua cost u
        jrb_insert_int(visited, u, new_jval_i(1));
        adjs = outgoingVertices(g, u);
        dll_traverse(n, adjs)
        {
            if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
            {
                node = jrb_find_int(cost, jval_i(dll_val(n))); //gia tri cua cost node
                i = getEdgeValue(g, u, jval_i(dll_val(n)));
                if (jval_i(node->val) > i + k)
                {
                    node->val = new_jval_i(i + k);

                    node = jrb_find_int(parent, jval_i(dll_val(n)));
                    if (node == NULL)
                    {
                        jrb_insert_int(parent, jval_i(dll_val(n)), new_jval_i(u));
                        node = jrb_find_int(parent, jval_i(dll_val(n)));
                    }
                    else
                        node->val = new_jval_i(u);
                }
                dll_append(q, dll_val(n));
            }
        }

        free_dllist(adjs);
    }
    u = jval_i(jrb_find_int(cost, dest)->val);

    printf("Do dai quang duong di la: %d km\nDuong di: ", u);
    path = findPath(parent, source, dest);
    dll_traverse(n, path)
        printf("%s ", getVertexName(g, jval_i(dll_val(n))));
    printf("\n");
    jrb_free_tree(visited);
    jrb_free_tree(cost);
    jrb_free_tree(parent);
    free_dllist(q);
    free_dllist(path);
    return u;
}

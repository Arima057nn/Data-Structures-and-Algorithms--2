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

void readFile(Graph g, FILE *ptr)
{
    int m, n, i, id, id1, id2;
    char name[30];
    double c;
    fscanf(ptr, "%d%d%*c", &m, &n);
    for (i = 0; i < m; i++)
    {
        fscanf(ptr, "%d%s%*c", &id, name);
        addVertex(g, id, name);
    }
    for (i = 0; i < n; i++)
    {
        fscanf(ptr, "%d%d%lf%*c", &id1, &id2, &c);
        addEdge(g, id1, id2, c);
    }
}

int readFile2(FILE *fptr, JRB Itemm)
{
    int soLuong, x;
    char sp[30];

    fscanf(fptr, "%d%*c", &soLuong);
    for (int i = 0; i < soLuong; i++)
    {
        fscanf(fptr, "%s%d%*c", sp, &x);
        // printf("%s ", sp);
        jrb_insert_str(Itemm, strdup(sp), new_jval_i(x));
    }
    return soLuong;
}
typedef struct SP
{
    char nameSP[30];
} SP;

int main(int argc, char *argv[])
{
    FILE *ptr, *fptr;
    Dllist F1, q;
    JRB node, p, Itemm = make_jrb(), familyF0 = make_jrb(), familyF1 = make_jrb();
    int m, n, soLuong;
    Graph g = createGraph();
    int choose, i, j;
    char f0[30], name[30];
    SP sp[10];
    int x[10];
    double c;
    while (1)
    {
        printf("======= MENU =======\n"
               "1.Doc du lieu\n"
               "2.Kiem tra kho\n"
               "3.Yeu cau mua hang\n"
               "4.Khai bao F0\n"
               "5.Nhom gia dinh can di xet nghiem\n"
               "6.Thoat va giai phong bo nho\n"
               "--->Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            ptr = fopen("map.txt", "r");
            fptr = fopen("item.txt", "r");
            soLuong = readFile2(fptr, Itemm);
            readFile(g, ptr);
            printf("Danh sach mat hang:\n");
            jrb_traverse(p, Itemm)
            {
                printf("%s ", jval_s(p->key));
            }
            printf("\n\nDanh sach ho gia dinh:\n");
            jrb_traverse(p, g.vertices)
            {
                if (jval_i(p->key) != 0)
                {
                    printf("%s ", getVertexName(g, jval_i(p->key)));
                }
            }
            printf("\n");
            break;
        case 2:
            printf("Kiem tra kho:\n");
            jrb_traverse(p, Itemm)
            {
                printf("%-20s:  %d san pham\n", jval_s(p->key), jval_i(p->val));
            }
            break;
        case 3:
            do
            {
                printf("Nhap ten ho gia dinh: ");
                c = getchar();
                gets(name);

            } while (getVertexId(g, name) == -1);
            i = 0;
            while (1)
            {
                printf("Nhap ten mat hang: ");
                gets(sp[i].nameSP);
                // printf("%s\n\n", sp);
                if (jrb_find_str(Itemm, strdup(sp[i].nameSP)) != NULL)
                {
                    printf("Nhap so luong muon mua: ");
                    scanf("%d", &x[i]);
                    printf("\n");
                    i++;
                }
                if (strcmp(sp[i].nameSP, "Done") == 0)
                {
                    break;
                }
            }
            for (j = 0; j < i; j++)
            {
                node = jrb_find_str(Itemm, strdup(sp[j].nameSP));
                if (x[j] > jval_i(node->val))
                {
                    printf("Mat hang %s trong kho khong du!\n", sp[j].nameSP);
                }
            }
            shortestPath(g, getVertexId(g, name), 0);
            break;
        case 4:
            printf("Nhap ten ho gia dinh F0: ");
            c = getchar();
            gets(f0);
            node = jrb_find_str(familyF0, strdup(f0));
            if (node != NULL)
                printf("Da ton tai");
            else
            {
                jrb_insert_str(familyF0, strdup(f0), new_jval_i(1));
            }

            printf("Danh sach ho gia dinh la F0: ");
            jrb_traverse(p, familyF0)
            {
                printf("%s ", jval_s(p->key));
            }
            printf("\n");
            break;
        case 5:
            jrb_traverse(p, familyF0)
            {
                // printf("%d", getVertexId(g, jval_s(p->key)));
                F1 = outgoingVertices(g, getVertexId(g, jval_s(p->key)));

                dll_traverse(q, F1)
                {
                    //printf("%s", getVertexName(g, jval_i(q->val)));
                    if (jrb_find_str(familyF1, strdup(getVertexName(g, jval_i(q->val)))) == NULL && jrb_find_str(familyF0, getVertexName(g, jval_i(q->val))) == NULL)
                    {
                        if (strcmp("Cho", getVertexName(g, jval_i(q->val))) != 0)
                        {
                            jrb_insert_str(familyF1, strdup(getVertexName(g, jval_i(q->val))), new_jval_i(1));
                        }
                    }
                }
            }
            printf("Danh sach cac ho can di xet nghiem ngay la: ");
            jrb_traverse(p, familyF1)
            {
                printf("%s ", jval_s(p->key));
            }
            printf("\n");
            break;
        case 6:
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

/* 
void printfVertex(int v)
{
  printf("%4d", v);
}
 */
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

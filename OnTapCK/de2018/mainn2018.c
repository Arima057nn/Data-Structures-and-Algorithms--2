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
int readCommand(int argc, char *argv[]);

int readFile1(Graph g, char *argv[])
{
    int n, a, i;
    char s[30];
    FILE *ptr = fopen(argv[2], "r");
    if (ptr == NULL)
    {
        printf("Cannot open the file\n");
        exit(0);
    }
    fscanf(ptr, "%d%*c", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(ptr, "%s%d%*c", s, &a);
        // addVertex(g, a, s);
        printf("%s %d\n", s, a);
    }
    return n;
}

int readFile2(Graph g, char *argv[], int M[])
{
    int n, a, b, i, m, j, id;
    char s[30], khoHang[30];
    double c;
    FILE *ptr = fopen(argv[3], "r");
    FILE *fptr = fopen(argv[2], "r");
    if (ptr == NULL || fptr == NULL)
    {
        printf("Cannot open the file\n");
        exit(0);
    }
    fscanf(ptr, "%d%*c", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(ptr, "%s%d%*c", s, &a);
        addVertex(g, a, s);
    }
    fscanf(fptr, "%d%*c", &m);
    for (i = 0; i < m; i++)
    {
        fscanf(fptr, "%s%d%*c", khoHang, &id);
        addVertex(g, -id, khoHang);
        M[i] = -id;
        // printf("%d\t", id);
        for (j = 0; j < n; j++)
        {
            fscanf(fptr, "%d%lf%*c", &a, &c);
            addEdge(g, -id, a, c);
        }
    }
    fscanf(fptr, "%d%*c", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(fptr, "%d%d%lf%*c", &a, &b, &c);
        // printf("%d %d %g\n", a, b, c);
        addEdge(g, -a, -b, c);
    }
    // for (i = 0; i < m; i++)
    // {
    //     printf("%d\t", M[i]);
    // }
    return m;
}
void inCase4(Graph g, int m, int M[])
{
    int i;
    Dllist node, p;
    for (i = 0; i < m; i++)
    {
        printf("%s\n", getVertexName(g, M[i]));
        node = outgoingVertices(g, M[i]);
        dll_traverse(p, node)
        {
            if (jval_i(p->val) > 0)
            {
                printf("%s %g\n", getVertexName(g, jval_i(p->val)), getEdgeValue(g, M[i], jval_i(p->val)));
            }
        }
    }
}
void inCase5(Graph g, char *argv[])
{
    int i;
    Dllist node, p;
    node = outgoingVertices(g, -atoi(argv[5]));
    dll_traverse(p, node)
    {
        if (jval_i(p->val) < 0)
        {
            printf("%s\n", getVertexName(g, jval_i(p->val)));
            printf("%s %g\n", getVertexName(g, atoi(argv[4])), getEdgeValue(g, jval_i(p->val), atoi(argv[4])));
        }
    }
}

void time(Graph g, char *argv[])
{
    double time = getEdgeValue(g, -atoi(argv[7]), -atoi(argv[6])) / 30 + 0.5;
    int t = (int)time;
    printf("thoi gian giao hang la %d gio %g phut", t, (time - t) * 60);
}
int main(int argc, char *argv[])
{
    Dllist p, list;
    JRB node;
    double c;
    int a, m, i, M[10];
    Graph g = createGraph();
    int choose;
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        printf("C-Advanced, HK20182\n");
        exit(0);
    }
    else if (argc == 3 && strcmp(argv[1], "-s") == 0)
    {
        readFile1(g, argv);
    }
    else
    {
        m = readFile2(g, argv, M);
        choose = readCommand(argc, argv);
        switch (choose)
        {
        case 3:
            a = hasEdge(g, -atoi(argv[4]), -atoi(argv[5]));
            if (a == -1)
                printf("-1");
            else
            {
                printf("%g", getEdgeValue(g, -atoi(argv[4]), -atoi(argv[5])));
            }

            break;
        case 4:
            inCase4(g, m, M);
            break;
        case 5:
            printf("%s\n", getVertexName(g, -atoi(argv[5])));
            printf("%s %g\n", getVertexName(g, atoi(argv[4])), getEdgeValue(g, -atoi(argv[5]), atoi(argv[4])));
            printf("---Cac kho ke la:\n");
            inCase5(g, argv);
            break;
        case 6:
            if (getEdgeValue(g, atoi(argv[4]), -atoi(argv[6])) >= atoi(argv[5]))
                printf("Dat hang thanh cong, thoi gian giao hang la 30p\n");
            else
            {
                if (getEdgeValue(g, atoi(argv[4]), -atoi(argv[6])) + getEdgeValue(g, atoi(argv[4]), -atoi(argv[7])) >= atoi(argv[5]))
                {
                    printf("Dat thang thanh cong, ");
                    time(g, argv);
                }
                else
                    printf("Dat hang khong thanh cong\n");
            }
            break;
        }
    }

    return 0;
}
//gcc -I ../../Libfdr/ -o qlykhang mainn2018.c ../../Libfdr/libfdr.a

int readCommand(int argc, char *argv[])
{
    // if (argc == 3 && strcmp(argv[1], "-s") == 0)
    // {
    //     return 2;
    // }
    if (argc == 4 && strcmp(argv[1], "-a") == 0)
    {
        return 4;
    }
    if (argc == 6)
    {
        if (strcmp(argv[1], "-w") == 0)
            return 3;
        if (strcmp(argv[1], "-h") == 0)
            return 5;
    }
    if (argc == 8 && strcmp(argv[1], "-g") == 0)
    {
        return 6;
    }
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

    printf("Do dai duong di la: %d\nDuong di: ", u);
    path = findPath(parent, source, dest);
    dll_traverse(n, path)
        printf("%s\n ", getVertexName(g, jval_i(dll_val(n))));
    printf("\n");
    jrb_free_tree(visited);
    jrb_free_tree(cost);
    jrb_free_tree(parent);
    free_dllist(q);
    free_dllist(path);
    return u;
}

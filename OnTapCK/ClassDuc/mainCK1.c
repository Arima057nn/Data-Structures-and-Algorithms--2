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

int readFile(Graph g, FILE *ptr)
{
    int n, id;
    char user[25];
    fscanf(ptr, "%d%*c", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(ptr, "%d%s%*c", &id, user);
        printf("%d  %s\n", id, user);
        addVertex(g, id, user);
    }
    return n;
}

// void readFile2(Graph g, FILE *fptr, int n)
// {
//     int id1, id2, i;
//     char c;
//     for (i = 0; i < n; i++)
//     {
//         fscanf(fptr, "%d%c", &id1, &c);
//         printf("%d ", id1);
//         if (c == '\n')
//             printf("\n");
//         else
//         {
//             while (fscanf(fptr, "%d%c", &id2, &c) == 2)
//             {
//                 addEdge(g, id1, id2, 1);
//                 printf("%d ", id2);
//                 if (c == '\n')
//                 {
//                     printf("\n");
//                     break;
//                 }
//             }
//         }
//     }
// }

// void readFile2(Graph g, FILE *fptr, int n)
// {
//     int i, id1, id2;
//     char c;
//     for (i = 0; i < n; i++)
//     {
//         c = '1';
//         fscanf(fptr, "%d", &id1);
//         while (c != '\n')
//         {
//             fscanf(fptr, "%c", &c);
//             if (c == '\n' || feof(fptr))
//                 break;
//             fscanf(fptr, "%d", &id2);
//             addEdge(g, id1, id2, 1);
//         }
//     }
//     // fclose(ptr);
// }

void readFile2(Graph g, FILE *fptr, int n)
{
    int id1, id2, i = 0;
    char c;
    while (i != n)
    {
        fscanf(fptr, "%d%c", &id1, &c);
        printf("%d ", id1);
        if (c == '\n')
            printf("\n");
        else
            while (fscanf(fptr, "%d%c", &id2, &c) == 2)
            {
                printf("%d ", id2);
                addEdge(g, id1, id2, 1);
                if (c != ' ')
                {
                    printf("\n");
                    break;
                }
            }
        i++;
    }
}

// void readFileFriends(Graph g, int numUsers)
// {

//     FILE *f;
//     char line[200];
//     f = fopen("friends.txt", "r");
//     if (f == NULL)
//     {
//         printf("Mo file friends.txt bi loi\n");
//     }
//     for (int i = 0; i < numUsers; i++)
//     {
//         fscanf(f, "%[^\n]%*c", line);
//         trim(line);
//         printf("%s\n", line);

//         char *token;
//         int j = 1, id1 = 0, id2 = 0;
//         token = strtok(line, " ");
//         while (token != NULL)
//         {
//             if (j == 1)
//             {
//                 id1 = atoi(token);
//                 //printf("%d ",id1);
//             }

//             if (j != 1)
//             {
//                 id2 = atoi(token);
//                 //printf("%d ",id2);
//             }
//             if (id2 != 0)
//             {
//                 addEdge(g, id1, id2, 1);
//                 //printf("%d %d\n",id1,id2);
//             }
//             token = strtok(NULL, " ");
//             j++;
//         }
//     }

//     fclose(f);
// }
int main(int argc, char *argv[])
{
    FILE *ptr, *fptr;
    Dllist node, listFriend;
    JRB p, list = make_jrb();
    int *A, x;
    char name[25], name1[25], name2[25];
    Graph g = createGraph();
    int choose, i, j, n;
    double c;
    while (1)
    {
        printf("\n======= MENU =======\n"
               "1.Input Data\n"
               "2.List Friend\n"
               "3.Popular person\n"
               "4.Check friend\n"
               "5.Suggest friend\n"
               "6.Exit\n"
               "--->Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            ptr = fopen("users1.txt", "r");
            fptr = fopen("friends1.txt", "r");
            n = readFile(g, ptr);
            printf("-----------------------\n");
            readFile2(g, fptr, n);

            break;
        case 2:
            printf("Nhap: ");
            c = getchar();
            gets(name);
            if (getVertexId(g, name) == -1)
            {
                printf("===> Nguoi nay khong ton tai\n");
                break;
            }
            if (outdegree(g, getVertexId(g, name)) == 0)
            {
                printf("===> Khong co ban\n");
                break;
            }

            listFriend = incomingVertices(g, getVertexId(g, name));
            dll_traverse(node, listFriend)
            {
                printf("==> %s\n", getVertexName(g, jval_i(node->val)));
            }
            break;
        case 3:
            // jrb_traverse(p, g.edges)
            // {
            //     // printf("%d\t", indegree(g, jval_i(p->key)));
            //     x = indegree(g, jval_i(p->key));
            //     jrb_insert_str(list, strdup(getVertexName(g, jval_i(p->key))), new_jval_i(x));
            // }
            // jrb_traverse(p, list)
            // {
            //     printf("%s\t%d", jval_s(p->key), jval_i(p->val));
            // }

            jrb_traverse(p, g.edges)
            {
                // printf("%d\t", indegree(g, jval_i(p->key)));
                x = indegree(g, jval_i(p->key));
                jrb_insert_int(list, x, new_jval_s(getVertexName(g, jval_i(p->key))));
            }
            jrb_rtraverse(p, list)
            {
                printf("%-20s\t%-20d\n", jval_s(p->val), jval_i(p->key));
            }
            break;
        case 4:
            printf("Nhap ng1: ");
            c = getchar();
            gets(name1);
            printf("Nhap ng2: ");
            gets(name2);
            if (hasEdge(g, getVertexId(g, name1), getVertexId(g, name2)) == 1)
            {
                printf("La ban be cua nhau\n");
            }
            else
                printf("Khong la ban be cua nhau\n");
            break;
        case 5:

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

Dllist outgoingVertices(Graph g, int v)
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

int outdegree(Graph g, int v)
{
    Dllist list, node;
    int count = 0;
    list = outgoingVertices(g, v);
    dll_traverse(node, list)
        count++;
    free_dllist(list);
    return count;
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

int indegree(Graph g, int v)
{
    Dllist list, node;
    int count = 0;
    list = incomingVertices(g, v);
    dll_traverse(node, list)
        count++;
    free_dllist(list);
    return count;
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

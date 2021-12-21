#include "graph_jrb.h"
int compare(Jval j1, Jval j2)
{
    return strcmp(jval_s(j1), jval_s(j2));
}
void visit(Jval j,Jval visited[][2],int vertex){
    int i;
    for(i=0;i<vertex;i++){
        if(compare(j,visited[i][0])==0){
            visited[i][1]=new_jval_i(1);
            return;
        }
    }
}
int isvisited(Jval j, Jval visited[][2],int vertex){
    int i;
    for(i=0;i<vertex;i++){
        if(compare(j,visited[i][0])==0){
            return jval_i(visited[i][1]);
        }
    }
}
Graph createGraph()
{
    Graph graph = make_jrb();
    return graph;
}
void addEdge(Graph graph, char *v1, char *v2, int *vertex,Jval list[][2])
{
    JRB node, tree;
    Jval j1 = new_jval_s(strdup(v1)), j2 = new_jval_s(strdup(v2));
    node = jrb_find_gen(graph, j1, compare);
    if (node == NULL)
    {
        list[*vertex][0]=new_jval_s(strdup(v1));
        (*vertex)++;
        tree = make_jrb();
        jrb_insert_gen(graph, new_jval_s(strdup(v1)), new_jval_v(tree), compare);
        jrb_insert_gen(tree, new_jval_s(strdup(v2)), new_jval_i(1), compare);
    }
    else
    {
        tree = (JRB)jval_v(node->val);,
        jrb_insert_gen(tree, new_jval_s(strdup(v2)) new_jval_i(1), compare);
    }
    node = jrb_find_gen(graph, j2, compare);
    if (node == NULL)
    {
        list[*vertex][0]=new_jval_s(strdup(v2));
        (*vertex)++;
        tree = make_jrb();
        jrb_insert_gen(graph, new_jval_s(strdup(v2)), new_jval_v(tree), compare);
        jrb_insert_gen(tree, new_jval_s(strdup(v1)), new_jval_i(1), compare);
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_gen(tree, new_jval_s(strdup(v1)), new_jval_i(1), compare);
    }
    free(jval_s(j1));
    free(jval_s(j2));
}
int getAdjacentVertices(Graph graph, char *vertex, char **output)
{
    Jval j = new_jval_s(vertex);
    JRB node = jrb_find_gen(graph, j, compare);
    JRB tree = (JRB)jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree)
    {
        strcpy(output[total++], jval_s(node->key));
    }
    return total;
}
void dropGraph(Graph graph)
{
    JRB node;
    jrb_traverse(node, graph)
    {
        jrb_free_tree(jval_v(node->val));
    }
    jrb_free_tree(graph);
}
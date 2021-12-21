#include <stdlib.h>
#include "graph_jrb_bfs.h"

Graph createGraph(){
    Graph graph = make_jrb();
    return graph;
}
void addEdge(Graph graph,int v1,int v2){
    JRB node,tree;
    node = jrb_find_int(graph,v1);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph,v1,new_jval_v(tree));
        jrb_insert_int(tree,v2,new_jval_i(1));
    }else{
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    node = jrb_find_int(graph,v2);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(graph,v2,new_jval_v(tree));
        jrb_insert_int(tree,v1,new_jval_i(1));
    }else{
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}
int getAdjacentVertices(Graph graph,int vertex,int *output){
    JRB node = jrb_find_int(graph,vertex);
    JRB tree = (JRB)jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree){
        output[total++] = jval_i(node->key);
    }
    return total;
}
void dropGraph(Graph graph){
    JRB node;
    jrb_traverse(node,graph){
        jrb_free_tree(jval_v(node->val));
    }
    jrb_free_tree(graph);
}
Dllist queue_initialize(){
    Dllist queue = new_dllist();
    return queue;
}
void enqueue(Dllist queue,int v){
    dll_append(queue,new_jval_i(v));
}
int isempty(Dllist queue){
    return dll_empty(queue);
};
int dequeue(Dllist queue){
    Dllist node = dll_first(queue);
    int v = jval_i(node->val);
    dll_delete_node(node);
    return v;
};
void printfVertex(int v){
    printf("%4d",v);
}
void BFS(Graph graph,int start, int stop, void (*func)(int)){
    int *visited=(int*)calloc(MAX,sizeof(int));
    int *output=(int*)calloc(MAX,sizeof(int));
    int u,total,i;
    Dllist queue = queue_initialize();   
    enqueue(queue,start);
    while(!isempty(queue)){
        u=dequeue(queue);
        if(visited[u] == 0){
            func(u);
            visited[u] = 1;
        }
        if(u==stop){
            break;
        }
        total=getAdjacentVertices(graph,u,output);
        for(i=0;i<total;i++){
            if(visited[output[i]]==0){
                enqueue(queue,output[i]);
            }
        }
    }
    free(visited);
    free(output);
}

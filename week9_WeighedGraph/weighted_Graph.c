#include "weighted_Graph.h"

Graph createGraph(int maxSize)
{
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

void addVertex(Graph g, int id, char *name)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL) // only add new vertex
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertexName(Graph g, int id)
{
    JRB node = jrb_find_int(g.vertices, id);

    if (node != NULL)
        return jval_s(node->val);
    else
        return NULL;
}

void addEdge(Graph g, int v1, int v2, double weight)
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
}

double getEdgeValue(Graph g, int v1, int v2)
{
    JRB node;
    if ((node = jrb_find_int(g.edges, v1)) != NULL)
    {
        if (jrb_find_int((JRB)(jval_v(node->val)), v2) != NULL)
            return jval_d(node->val);
        else
            return INFINITIVE_VALUE;
    }
    else
        return INFINITIVE_VALUE;

}; // return INFINITIVE_VALUE if no edge between v1 and v2 int indegree(Graph graph, int v, int *output);

int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
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

int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
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

double shortestPath(Graph g, int s, int t, int *path, int *length)
{
   double distance[1000], min, w, total; // distance khoang cach
   int previous[1000], tmp[1000];
   int n, output[100], i, u, v, start;
   Dllist ptr, queue, node;

   for (i = 0; i < 1000; i++)
      distance[i] = INFINITIVE_VALUE;
   distance[s] = 0;
   previous[s] = s;

   queue = new_dllist();
   dll_append(queue, new_jval_i(s));

   while (!dll_empty(queue))
   {
      // get u from the priority queue
      min = INFINITIVE_VALUE;
      dll_traverse(ptr, queue)
      {
         u = jval_i(ptr->val);
         if (min > distance[u])
         {
            min = distance[u];
            node = ptr;
         }
      }
      dll_delete_node(node);

      if (u == t)
         break; // stop at t

      n = outdegree(g, u, output);
      for (i = 0; i < n; i++)
      {
         v = output[i];
         w = getEdgeValue(g, u, v);
         if (distance[v] > distance[u] + w)
         {
            distance[v] = distance[u] + w;
            previous[v] = u;
         }
         dll_append(queue, new_jval_i(v));
      }
   }
   total = distance[t];
   if (total != INFINITIVE_VALUE)
   {
      tmp[0] = t;
      n = 1;
      while (t != s)
      {
         t = previous[t];
         tmp[n++] = t;
      }
      for (i = n - 1; i >= 0; i--)
         path[n - i - 1] = tmp[i];
      *length = n;
   }
   return total;
}


void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

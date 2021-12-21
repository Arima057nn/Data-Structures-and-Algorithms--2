#include "graph.h"

Graph createGraph(int maxSize)
{
  Graph g = make_jrb();
  return g;
}

void addEdge(Graph g, int v1, int v2)
{
  JRB node, l;

  node = jrb_find_int(g, v1);
  if (node != NULL)
  {
    l = (JRB)jval_v(node->val);
    jrb_insert_int(l, v2, new_jval_i(1));
  }
  else
  {
    l = make_jrb();
    jrb_insert_int(l, v2, new_jval_i(1));
    jrb_insert_int(g, v1, new_jval_v(l));
  }

  node = jrb_find_int(g, v2);
  if (node != NULL)
  {
    l = (JRB)jval_v(node->val);
    jrb_insert_int(l, v1, new_jval_i(1));
  }
  else
  {
    l = make_jrb();
    jrb_insert_int(l, v1, new_jval_i(1));
    jrb_insert_int(g, v2, new_jval_v(l));
  }
}

int isAdjacent(Graph g, int v1, int v2)
{
  JRB node;

  if ((node = jrb_find_int(g, v1)) != NULL)
  {
    if (jrb_find_int((JRB)(jval_v(node->val)), v2) != NULL)
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

Dllist getAdjacentVertices(Graph g, int v)
{
  int n = 0;
  JRB node, l, i;
  Dllist output = new_dllist();
  if ((node = jrb_find_int(g, v)) == NULL)
    return output;

  l = (JRB)jval_v(node->val);
  jrb_traverse(i, l)
  {
    dll_append(output, i->key);
  }
  return output;
}

void dropGraph(Graph g)
{
  JRB i;

  jrb_traverse(i, g)
  {
    jrb_free_tree((JRB)jval_v(i->val));
    jrb_free_tree(g);
  }
}
void BFS(Graph g, int v, void (*f)(int key))
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
      f(u);
      jrb_insert_int(visited, u, new_jval_i(1));
      adjs = getAdjacentVertices(g, u);

      dll_traverse(n, adjs)
      {
        if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
          dll_append(q, dll_val(n));
      }

      free_dllist(adjs);
    }
  }
  jrb_free_tree(visited);
  free_dllist(q);
}

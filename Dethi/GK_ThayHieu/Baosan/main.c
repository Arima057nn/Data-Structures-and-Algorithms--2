#include <stdio.h>
#include <stdlib.h>
#include "undirected_graph.h"

int bai3a(Graph g, int v);
void bai3b(Graph g);

int main()
{
  FILE *ptr;
  int i, k, n, m;
  int a, b, c;
  int **M;
  Graph g = createGraph();
  JRB node;
  Dllist dske, nodedll;

  while (1)
  {
    printf("\n\n1.Doc ban do va in ma tran ke\n"
           "2.In danh sach ke cua moi thanh tri\n"
           "3.Dua ra danh sach thanh tri theo yeu cau\n"
           "4.Tim duong di ngan nhat\n"
           "5.Tim duong di bo ngan nhat\n"
           "6.Thoat\n"
           "Lua chon: ");
    scanf("%d%*c", &k);
    switch (k)
    {
    case 1:
      if ((ptr = fopen("dothi.txt", "r")) == NULL)
      {
        printf("Cannot find dothi.txt file!\n");
        return 1;
      }
      fscanf(ptr, "%d%d%*c", &n, &m);
      M = (int **)malloc(n * sizeof(int *));

      for (i = 0; i < (n + 1); i++)
      {
        M[i] = (int *)calloc(n + 1, sizeof(int));
      }

      for (i = 0; i < m; i++)
      {
        fscanf(ptr, "%d%d%d%*c", &a, &b, &c);
        addVertex(g, a, "1");
        addVertex(g, b, "1");
        addEdge(g, a, b, c);
        M[a][b] = c;
        M[b][a] = c;
      }
      printf("Doc du lieu thanh cong!\nMa tran ke:\n");
      for (i = 1; i < (n + 1); i++)
      {
        for (a = 1; a < (n + 1); a++)
        {
          printf("%4d", M[i][a]);
        }
        printf("\n");
      }
      for (i = 0; i < (n + 1); i++)
      {
        free(M[i]);
      }
      free(M);

      break;
    case 2:
      jrb_traverse(node, g.vertices)
      {
        printf("Castle %d: ", jval_i(node->key));
        dske = outgoingVertices(g, jval_i(node->key));
        dll_traverse(nodedll, dske)
        {
          printf("%4d", jval_i(dll_val(nodedll)));
        }
        printf("\n");
        free_dllist(dske);
      }
      break;
    case 3:
      printf("Thanh tri chi co the di bo: ");
      jrb_traverse(node, g.vertices)
      {
        if (bai3a(g, jval_i(node->key)))
          printf("%4d", jval_i(node->key));
      }
      printf("\n");
      printf("Thanh tri co nhieu duong di noi truc tiep nhat: ");
      bai3b(g);
      printf("\n");
      break;
    case 4:
      printf("Nhap thanh tri xuat phat: ");
      scanf("%d%*c",&a);
      printf("Nhap thanh tri dich: ");
      scanf("%d%*c",&b);
      shortestPath(g,a,b);
      break;
    case 5:

      break;
    case 6:
      dropGraph(g);
      return 0;
      break;
    }
  }

  return 0;
}

int bai3a(Graph g, int v)
{
  JRB node;
  Dllist dske, nodedll;
  dske = outgoingVertices(g, v);
  dll_traverse(nodedll, dske)
  {
    if (getEdgeValue(g, v, jval_i(dll_val(nodedll))) < 50)
    {
      free_dllist(dske);
      return 0;
    }
  }
  free_dllist(dske);
  return 1;
}

void bai3b(Graph g)
{
  JRB node;
  Dllist dske, nodedll;
  int max, i;
  jrb_traverse(node, g.vertices)
  {
    dske = outgoingVertices(g, jval_i(node->key));
    i = 0;
    dll_traverse(nodedll, dske)
    {
      i++;
    }
    if (i > max)
      max = i;
    free_dllist(dske);
  }
  jrb_traverse(node, g.vertices)
  {
    dske = outgoingVertices(g, jval_i(node->key));
    i = 0;
    dll_traverse(nodedll, dske)
    {
      i++;
    }
    if (i == max)
      printf("%4d", jval_i(node->key));
    free_dllist(dske);
  }
}

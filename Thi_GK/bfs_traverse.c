#include "graph_jrb.h"
#define sizemax 100
int main()
{
    int k, i, j, n, vertex = 0;
    char v1[sizemax], v2[sizemax], **output, **output2;
    // Output de chua mang cac dinh lien ke
    // Output2 chua mang cac dinh lien ke cua cac dinh chua trong output
    // list la mang 2 chieu, Hang dau luu ten nguoi dung , hang 2 la luu so ban be
    // visited la luu cac dinh da tham. Dinh nao da tham roi thi kkhong tham nua
    FILE *ptr;
    Graph g = createGraph();
    Jval list[sizemax][2], visited[sizemax][2];
    while (1)
    {
        printf("\n\nDo thi Friendship\n\n"
               "1.Doc file va in ra so dinh, so canh\n"
               "2.In ra danh sach ban be\n"
               "3.In ra man hinh thanh vien co so ban be tang dan\n"
               "4.In ra danh sach thanh vien co chung ban be\n"
               "5.Thoat\n"
               "Choose: ");
        scanf("%d%*c", &k);
        switch (k)
        {
        case 1:
            if ((ptr = fopen("/home/revgato/C Advanced/dethi/de1/friendship.txt", "r")) == NULL)
            {
                printf("Cannot open friendship.txt file!\n");
                return 1;
            }
            fscanf(ptr, "%d%*c", &n);
            while (fscanf(ptr, "%*c%[^\"]%*c%*c%[^\"]%*c%*c", v1, v2) == 2)
            {
                addEdge(g, v1, v2, &vertex, list);
            }
            output = (char **)malloc(vertex * sizeof(char *));
            output2 = (char **)malloc(vertex * sizeof(char *));
            for (i = 0; i < vertex; i++)
            {
                visited[i][0] = new_jval_s(strdup(jval_s(list[i][0])));
                list[i][1] = new_jval_i(0);
                output[i] = (char *)malloc(sizemax * sizeof(char));
                output2[i] = (char *)malloc(sizemax * sizeof(char));
            }
            printf("So dinh: %d\nSo canh: %d\n", vertex, n);
            break;
        case 2:
            printf("Nhap ten: ");
            scanf("%s", v1);
            n = getAdjacentVertices(g, v1, output);
            if (n == 0)
                printf("%s khong co ban be!\n", v1);
            else
            {
                printf("Danh sach ban be cua %s:\n", v1);
                for (i = 0; i < n; i++)
                    printf("%s\n", output[i]);
            }
            break;
        case 3:
            for (i = 0; i < vertex; i++)
            {
                list[i][1] = new_jval_i(getAdjacentVertices(g, jval_s(list[i][0]), output));
            }
            for (i = 1; i < vertex; i++)
            {
                printf("%d\t", i);
                for (n = 0; n < vertex; n++)
                {
                    if (jval_i(list[n][1]) == i)
                    {
                        printf("\"%s\"   ", jval_s(list[n][0]));
                    }
                }
                printf("\n");
            }
            break;
        case 4:
            printf("Nhap ten: ");
            scanf("%s%*c", v1);
            for (i = 0; i < vertex; i++)
            {
                visited[i][1] = new_jval_i(0);
            }
            visit(new_jval_s(v1), visited, vertex);
            n = getAdjacentVertices(g, v1, output);
            for (i = 0; i < n; i++)
            {
                k = getAdjacentVertices(g, output[i], output2);
                for (j = 0; j < k; j++)
                {
                    if (isvisited(new_jval_s(output2[j]), visited, vertex) == 0)
                    {
                        visit(new_jval_s(output2[j]), visited, vertex);
                        printf("\"%s\"  ", output2[j]);
                    }
                }
                printf("\n");
            }
            break;
        case 5:
            dropGraph(g);
            for (i = 0; i < vertex; i++)
            {
                //free(output[i]);
                free(jval_s(list[i][0]));
                free(jval_s(visited[i][0]));
            }
            free(output);
            printf("\n\n");
            return 0;
        default:
            printf("Vui long chon tu 1-5\n\n");
            break;
        }
    }
}
//gcc -I libfdr/ -o dethi/de1/program dethi/de1/main_jrb.c dethi/de1/graph_jrb.c libfdr/libfdr.a

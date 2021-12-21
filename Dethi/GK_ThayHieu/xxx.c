#include <stdio.h>
#include <stdlib.h>

void init(int arr[][V])
{
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            arr[i][j] = 0;
}

void add_edge(int arr[][V], int i, int j)
{
    arr[i][j] = 1;
    arr[j][i] = 1;
}

void print(int arr[][V])
{
    for (int i = 0; i < V; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < V; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int matrix[V][V];
    init(matrix);
    add_edge(matrix, 2, 3);
    add_edge(matrix, 2, 4);
    add_edge(matrix, 3, 4);
    add_edge(matrix, 4, 2);
    add_edge(matrix, 4, 5);
    print(matrix);
    return 0;
}

// Do thi vo huong co trong luong
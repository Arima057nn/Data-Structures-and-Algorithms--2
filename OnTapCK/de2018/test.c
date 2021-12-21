#include <stdio.h>

void ham(int n, int M[])
{

    M[0] = 1;
    M[1] = 2;
    M[2] = 3;
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", M[i]);
    }
}
int main()
{
    int n = 3;
    int N[n];
    ham(n, N);
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", N[i]);
    }
    return 0;
}
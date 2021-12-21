#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int i = 0, j = 0;
    char C, B;
    int a, b;
    FILE *ptr = fopen("pageConnection.txt", "r");
    if (ptr == NULL)
    {
        printf("Cannot open the file\n");
        return 1;
    }
    fscanf(ptr, "%d%c", &n, &C);
    for (i = 0; i < n; i++)
    {
        B = '1';
        fscanf(ptr, "%d", &a);
        printf("vui");
    }
    while (B != '\n')
    {
        fscanf(ptr, "%c", &B);
        printf("vui");
        if (B == C || feof(ptr))
            break;
        fscanf(ptr, "%d", &b);
    }

    fclose(ptr);
    return 0;
}
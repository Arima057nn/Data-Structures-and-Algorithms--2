#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int i = 0, j = 0;
    int A[50];
    char c;
    FILE *fptr = fopen("pageConnection.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open the file\n");
        return 1;
    }
    fscanf(fptr, "%d%*c", &n);
    while (j != n)
    {
        while (fscanf(fptr, "%d%c", &A[i], &c) == 2)
        {
            printf("%d\t", A[i]);
            i++;
            if (c != ' ')
                break;
        }

        j++;
    }

    fclose(fptr);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int getID(char *A)
{
    for (int i = 0; i < strlen(A); i++)
        if (isdigit(A[i]))
            return atoi(&A[i]);
}

int main()
{
    FILE *ptr = fopen("exam.txt", "r");
    int dest, soucre;
    double time;
    char A[100], B, C = '\n';
    while (!feof(ptr))
    {
        fscanf(ptr, "%s%*c%*c%c", A, &B);
        dest = getID(A);
    }

    return 0;
}
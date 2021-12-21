#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *ptr;
    char s[10], s1[10];
    int a;
    char c;
    ptr = fopen("demo.txt", "r");
    if (ptr == NULL)
    {
        printf("Cannot open the file");
        return 1;
    }
    while (1)
    {
        }
    return 0;
}
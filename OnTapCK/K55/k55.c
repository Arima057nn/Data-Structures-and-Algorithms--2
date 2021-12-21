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
        fscanf(ptr, "%s%c", s, &c);
        printf("%s%c", s, s);
        fscanf(ptr, "%c", &c);

        if (c != '\n')
        {
        }

        while (fscanf(ptr, "%[^-]%c%d", s1, &c, &a) == 3)
        {
            printf("%s\t%d", s1, a);
        }

        if (c != '\n')
            break;
    }
    return 0;
}
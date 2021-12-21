#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max 1000000
typedef int element;

int randome(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

int int_compare(void *x, void *y)
{
    int m, n;
    m = *((int *)x);
    n = *((int *)y);
    if (m == n)
        return 0;
    return m > n ? 1 : -1;
}
int main()
{
    int  i;
    int n = 10;
    int a[10] = { 2,3,42,4,66,34,-34,-34,0,10};
    
       qsort(a, n, sizeof(int), int_compare);
    for(i = 0;i < 10;i++){
        printf("%d\t",a[i]);
    }
    return 0;
}

/* int main()
{
    int i, n;
    int A[10] = { 2,3,42,4,66,34,-34,-34,0,10};
    
    
   
    qsort(A,10,sizeof(int),int_compare);
    
    
    return 0;
}
 */
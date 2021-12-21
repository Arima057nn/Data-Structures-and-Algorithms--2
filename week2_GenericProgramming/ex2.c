#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define MAX 1000000

int randome(int min, int max)
{
    return min + rand() % (max + 1 - min);
}
int *createArray(int size)
{
    int i;
    int *A = malloc(sizeof(int) * size);
    for (i = 0; i < size; i++)
    {
        A[i] = randome(0, 10);
    }
    return A;
}

void exch(void *buf, int size, int a, int b)
{
    void *temp = malloc(size);
    memcpy(temp,(char*)buf + a*size,size);
    memcpy((char*)buf + a*size, (char*)buf + b*size, size);
    memcpy((char*)buf + b*size,temp, size);
    free(temp);
}

int compare(void const *item1, void const *item2){
    int m,n;
    m = *((int*)item1);
    n = *((int*)item2);
    if(m == n) return 0;
    else if(m < n) return -1;
    else return 1;
}

void threeWayPartition(void *a, int size, int l, int r, int (*compare)(const void *,const void *))
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (compare((char *)a + (++i) * size, (char *)a + r * size) < 0)
            ;
        while (compare((char *)a + r * size, (char *)a + (--j) * size) < 0)
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a, size, i, j);
        if (compare((char *)a + i * size, (char *)a + r * size) == 0)
            exch(a, size, ++p, i);
        if (compare((char *)a + j * size, (char *)a + r * size) == 0)
            exch(a, size, --q, j);
    }
    exch(a, size, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        exch(a, size, k, j--);
    for (int k = r - 1; k >= q; k--)
        exch(a, size, k, i++);
    threeWayPartition(a, size, l, j, compare);
    threeWayPartition(a, size, i, r, compare);
}
void printArray(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return;
}

int *DumpArray(int *p, int size)
{
    int *a = malloc(sizeof(int) * size);
    memcpy(a, p, sizeof(int) * size);
    return a;
}

void quickSort(int list[], int left, int right)
{
    int pivot, i, j;
    int temp;
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = list[left];
        do
        {
            do
            {
                i++;
            } while (list[i] < pivot);
            do
            {
                j--;
            } while (list[j] > pivot);
            if (i < j)
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
                //swap(list,i,j);
            }
        } while (i < j);
        temp = list[left];
        list[left] = list[j];
        list[j] = temp;
        quickSort(list, left, j - 1);
        quickSort(list, j + 1, right);
    }
}

int search(void *buf,int size,int l, int r,void *item,int (*compare)(void *, void *))
{
    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = compare(item, (char *)buf + (size * i));
    if (res == 0)
        return i;
    else if (res < 0)
        return search(buf, size, l, i - 1, item, compare);
    else
        return search(buf, size, i + 1, r, item, compare);
}
int main()
{
    int *A, *B, n;
    int i;
    clock_t start, end;
    srand((int)time(0));
    printf("Nhap n: ");
    scanf("%d", &n);
    A = createArray(n);
    B = DumpArray(A, n);
    for (i = 0; i < n; i++)
    {
        printf("%d\t", A[i]);
    }
    printf("\n");
    start = clock();
    threeWayPartition(A, sizeof(int), 0, n, compare);
    end = clock();
    printf("3 way partition: %f\n", (float)(end - start) / CLOCKS_PER_SEC);
    for (i = 0; i < n; i++)
    {
        printf("%d\t", A[i]);
    }
    printf("\n");
    start = clock();
    quickSort(B, 0, n);
    end = clock();
    printf("quick sort: %f\n", (float)(end - start) / CLOCKS_PER_SEC);
    for (i = 0; i < n; i++)
    {
        printf("%d\t", B[i]);
    }
    printf("\n");

    free(A);
    free(B);
    return 0;
}

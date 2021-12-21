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
int *createArray(int size){
    int i;
    int *A = (int*)malloc(sizeof(int) * size);
    for(i = 0;i < size; i++){
        A[i] = randome(0,10);
    }
    return A;
}
void selection_sort(int a[], int n)
{
    int i, j, min, tmp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j <= n - 1; j++)
            if (a[j] < a[min])
                min = j;
        tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
    }
}

void exch(int list[], int a, int b)
{
    int temp;
    temp = list[a];
    list[a] = list[b];
    list[b] = temp;
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

void ThreeWayPartition(int a[], int l, int r)
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (a[++i] < a[r])
            ;
        while (a[r] < a[--j])
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a, i, j);
        if (a[i] == a[r])
            exch(a, ++p, i);
        if (a[j] == a[r])
            exch(a, --q, j);
    }
    exch(a, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        exch(a, k, j--);
    for (int k = r - 1; k >= q; k--)
        exch(a, k, i++);
    ThreeWayPartition(a, l, j);
    ThreeWayPartition(a, i, r);
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

int *DumpArray(int *p, int size){
  int *a=malloc(sizeof(int) * size);
  memcpy(a, p, sizeof(int) * size);
  return a;
}
int main()
{
    int *A,*B,*C,size;
    clock_t start,end;
    srand((int)time(0));
    printf("Nhap size: ");  
    scanf("%d",&size);
    A = createArray(size);
    B = DumpArray(A,size);
    C = DumpArray(A,size);

    start = clock();    
    ThreeWayPartition(A, 0, size);
    end = clock();
    printf("3 way partition: %f\n", (float)(end - start) / CLOCKS_PER_SEC);

    start = clock();    
    quickSort(B, 0, size);
    end = clock();
    printf("quick sort: %f\n", (float)(end - start) / CLOCKS_PER_SEC);
    
    free(A);
    free(B);
    free(C);
    /* start = clock();    
    selection_sort(C,size);
    end = clock();
    printf("selection sort: %f\n", (float)(end - start) / CLOCKS_PER_SEC);
    printf("\n"); */
    return 0;
}

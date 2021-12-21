#include <stdio.h>
#include "jval.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RANDMAX 100
#define NUMBER 10
void exch(void *buf, int i, int j)
{
    Jval tmp;
    memcpy(&tmp, buf + i * sizeof(Jval), sizeof(Jval));
    memcpy(buf + i * sizeof(Jval), buf + j * sizeof(Jval), sizeof(Jval));
    memcpy(buf + j * sizeof(Jval), &tmp, sizeof(Jval));
}
void sort_gen(Jval a[], int l, int r, int (*compare)(Jval *, Jval *))
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (compare(&a[++i], &a[r]) < 0)
            ;
        while (compare(&a[r], &a[--j]) < 0)
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a, i, j);
        if (compare(&a[i], &a[r]) == 0)
            exch(a, ++p, i);
        if (compare(&a[j], &a[r]) == 0)
            exch(a, --q, j);
    }
    exch(a, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        exch(a, k, j--);
    for (int k = r - 1; k >= q; k--)
        exch(a, k, i++);
    sort_gen(a, l, j, compare);
    sort_gen(a, i, r, compare);
}

int search_gen(Jval a[], int l, int r, Jval item, int (*compare)(Jval *, Jval *))
{
    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = compare(&item, a + i);
    if (res == 0)
        return i;
    else if (res > 0)
        return search_gen(a, i + 1, r, item, compare);
    else
        return search_gen(a, l, i - 1, item, compare);
}


Jval *create_array_i(int size)
{
    srand((int)time(0));
    Jval *array = (Jval *)malloc(size * sizeof(Jval));
    for (int i = 0; i < size; i++)
    {
        array[i] = new_jval_i(rand() % RANDMAX);
    }
    return array;
}

int compare_i(Jval *a, Jval *b)
{
    if (jval_i(*a) == jval_i(*b))
        return 0;
    return jval_i(*a) < jval_i(*b) ? -1 : 1;
}

void sort_i(Jval a[], int l, int r)
{
    sort_gen(a, l, r, compare_i);
}

int search_i(Jval a[], int l, int r, int x)
{
    return search_gen(a, l, r, new_jval_i(x), compare_i);
}

void print_arr_i(Jval a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", jval_i(a[i]));
    }
    printf("\n");
}

int main(){
  Jval *a=create_array_i(NUMBER);
  int i;
  printf("Before sort:\n");
  print_arr_i(a,NUMBER);
  sort_i(a,0,NUMBER-1);
  printf("After:\n");
  print_arr_i(a,NUMBER);
  printf("Input number you want to search: ");
  scanf("%d",&i);
  printf("Result: %d\n",search_i(a,0,NUMBER-1,i));
  return 0;
}

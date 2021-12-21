#include <stdio.h>
#include <string.h>
#include "Jval.h"


int randome(int min, int max)
{
    return min + rand() % (max + 1 - min);
}
Jval *createArray_i(int n){
    int i;
    Jval *A = (Jval*)malloc(sizeof(Jval) *  n);
    for(i = 0;i < n; i++){
        A[i] = randome(0,20);
    }
    return A;
}

int compare_i(Jval *a, Jval *b){
    if( jval_i(*a) == jval_i(*b)) return 0;
    else if( jval_i(*a) < jval_i(*b)) return -1;
    else return 1;
}
void exch_t(Javl *a, Jval *b){
    int temp;
    temp = jval_i(*a);
    jval_i(*a) = jval_i(*b);
    jval_i(*b) = temp; 
}

void sort_i(Jval a[],int left)
int main(){
    Jval a,b;
    


    return 0;
}
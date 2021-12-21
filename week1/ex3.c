#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* void *memcpy(void *A,const void *B,size n){
    const char *first = (const char*)B;
    conse char *last = ((const char*)B) + n;
    char* result = 

} */
int randome(int min, int max)
{
    return min + rand() % (max + 1 - min);
}
int *createArray(int size){
    int i;
    int *A = malloc(sizeof(int) * size);
    for(i = 0;i < size; i++){
        A[i] = randome(0,20);
    }
    return A;
}
int *DumpArray(int *p, int size){
  int *a=malloc(sizeof(int) * size);
  memcpy(a, p, sizeof(int) * size);
  return a;
}
int main(){
    /* int i;
    int *A = (int*)malloc(2 * sizeof(int));
    A[0] = 1;
    A[1] = 2;
    for(i = 0; i < 2;i++){
        printf("%d\t",A[i]);
    } 
    printf("\n");
    int *B = (int*)malloc(2 * sizeof(int));
    memcpy(B,A,2 * sizeof(int));  
    for(i = 0; i < 2;i++){
        printf("%d\t",B[i]);
    } */

    int i;
    int A[2] = {1, 2};
    int B[2];
    memcpy(&B,&A,2 * sizeof(int));  
    for(i = 0; i < 2;i++){
        printf("%d\t",B[i]);
    }
    return 0;
}
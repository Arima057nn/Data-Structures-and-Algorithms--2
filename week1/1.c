#include <stdio.h>

void swap(int list[],int a,int b){
    int temp;
    temp = list[a];
    list[a] = list[b];
    list[b] = temp;

}

void swap2(int *a,int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;

}
void print(int A[]){
    int i;
    for(i = 0;i <5;i++){
        printf("%ld\t",(&A[i]));
    }
    //  *(&A[i]) = 6;
}
int main(){
    int i;
    int A[5] = {0,1,2,3,4};
    printf("\n");
    swap(A,2,4);
    //printf("%d",A[0]);
    //*(&A[4]) = 5; 
    swap2(&A[2],&A[4]);
    for(i = 0;i <5;i++){
        printf("%d",*(&A[i]));
    }
    //swap(&A,2,3);
    
    return 0;
}
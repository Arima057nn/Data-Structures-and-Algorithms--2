#include <stdio.h>
#include <stdlib.h>
#define MAX 10
int bac(int *A){
    int a=0,i;
    for(i=0;i<MAX;i++){
        if(A[i]==1){
            a++;
        }
    }
    return a;
}
int isover(int *B){
    for(int i=0;i<MAX;i++){
        if(B[i]==1){
            return 1;
        }
    }
    return 0;
}
int color(int *C,int *A,int a){
    int c=1;
    for(int i=0;i<MAX;i++){
        if(C[i]==c){
            if(A[a*MAX+i]==0){
                return c;
            }
            c++;
        }
    }
    return c;
}
int main(){
    FILE *ptr1,*ptr2;
    int *A=(int*)calloc(MAX*MAX,sizeof(int));
    int *B=(int*)calloc(MAX,sizeof(int));
    int *C=(int*)calloc(MAX,sizeof(int));
    char mau[10][MAX]={"aa","red","green","blue","yellow","white","brown","orange"};
    int a,b,c,d,max,i;
    ptr1=fopen("dothi.txt","r");
    ptr2=fopen("dothitomau.dot","w");
    fscanf(ptr1,"%d%d",&d,&c);
    while(fscanf(ptr1,"%d%d",&a,&b)==2){
        A[a*MAX+b]=1;
        A[b*MAX+a]=1;
    }
    for(i=0;i<MAX;i++){
        B[i]=bac(&A[i*MAX]);
    }
    while(isover(B)){
        max=0;
        for(i=0;i<MAX;i++){
            if(B[i]>max){
                max=B[i];
                a=i;
            }
        }
        B[a]=0;
        C[a]=color(C,A,a);
    }
    fprintf(ptr2,"graph dothi\n{\n");
    for(i=0;i<MAX;i++){
        if(C[i]!=0){
            fprintf(ptr2,"%d [fillcolor=%s, style=filled];\n",i,mau[C[i]]);
        }
    }
    fseek(ptr1,SEEK_SET,0);
    fscanf(ptr1,"%d%d",&d,&c);
    while(fscanf(ptr1,"%d%d",&a,&b)==2){
        fprintf(ptr2,"%d -- %d;\n",a,b);
    }
    fprintf(ptr2,"}");
    fclose(ptr1);
    fclose(ptr2);
    free(A);
    free(B);
    free(C);
}
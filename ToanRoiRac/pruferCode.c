#include <stdio.h>
#define MAX 100
int find(int *b,int n){
  int i;
  for(i=1;i<n+1;i++){
    if(b[i]==1){
      b[i]--;
      return i;
    }
  }
}

int main(){
  int n,i,j,k;
  int a[2][MAX],b[MAX];
  printf("Nhap du lieu vao:\n");
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d%d",&a[0][i],&a[1][i]);
  }
  for(i=0;i<n+1;i++){
    b[i]=0;
  }
  for(i=0;i<n;i++){
    b[a[0][i]]++;
    b[a[1][i]]++;
  }
  i=0;
  printf("Prufer code: ");
  while(i<n-1){
    j=find(b,n);
    for(k=0;k<n;k++){
            if(a[0][k]==j){
	      printf("%d ",a[1][k]);
	      b[a[1][k]]--;
	      a[0][k]=a[1][k]=-1;
            }
            if(a[1][k]==j){
	      printf("%d ",a[0][k]);
	      b[a[0][k]]--;
	      a[0][k]=a[1][k]=-1;
            }
    }
    i++;
  }
  printf("\n");
}

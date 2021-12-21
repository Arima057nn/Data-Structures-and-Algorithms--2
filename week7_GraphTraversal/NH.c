#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char name[10];
} Name;

int main(){
  Name A[16];
  int i = 0;
  int B,j;
  FILE *ptr = fopen("A.txt","r");
  if (ptr == NULL){
    printf("cannot open the file");
    return 1;
  }
  fscanf(ptr,"%d%*c",&B);
  while(fscanf(ptr,"%*c %[^-] %*c %*c %[^-] %*c %*c",A[i].name,A[i+1].name) == 2){
    i = i + 2;
  }
   j = i;
  for(i = 0; i < j; i++){
    printf("%-20s\n",A[i].name);

  }
  printf("\n");
  return 0;
}

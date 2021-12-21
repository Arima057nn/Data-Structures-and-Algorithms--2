#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_compare(void *item1, void *item2){
    int m,n;
    m = *((int*)item1);
    n = *((int*)item2);
    if(m == n) return 0;
    else if(m < n) return -1;
    else return 1;
}

/* int search(void *buf, int size, int left, int right, void *item){

    int i,res;
    if(right < left) return -1;
    i = (l+r)/2;
    res = compare(item)
}
 */
int main(){
    int resuft;
    int a = 3,b = 2;
    resuft = int_compare(&a,&b);
    printf("%d",resuft);


    return 0;
}
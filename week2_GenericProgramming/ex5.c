#include <stdio.h>

typedef union ex5
{
    int i;
    char c;
} Jval;

int main(){
    Jval v;
    v.i = 3;
    v.c = 'a';
    printf("%d\n",v.i);


    return 0;
}
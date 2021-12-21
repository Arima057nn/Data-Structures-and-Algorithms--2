#include <stdio.h>

#include "jval.h"
int main(){
    Jval v;
    v = new_jval_i(10);
    printf("%d\n",jval_i(v));


    return 0;
}
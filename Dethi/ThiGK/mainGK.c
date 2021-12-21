#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

void print_entry(char *dn, char *ip)
{
  printf("%s => %s\n", dn, ip);
}


int main()
{
    JRB list = make_jrb();
    int n;
    char IP[100], Name[100];
    FILE *ptr = fopen("dns.txt", "r");
    if (ptr == NULL)
    {
        printf("Error\n");
        exit(0);
    }
    fscanf(ptr, "%d%*c", &n);
    while( fscanf(ptr,"%s%*c%s*c",Name,IP) == 2){
        //printf("%s\t%s\n",Name,IP);
        print_entry(Name,IP);
        jrb_insert_str(list,strdup(Name),new_jval_s(strdup(IP)));
    }
    fclose(ptr);

    return 0;
}
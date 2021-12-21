#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRY 1000

typedef struct PhoneEntry
{
    int number;
    char name[50];
} PhoneEntry;
struct PhoneEntry *A;

void initialize(){
    A = malloc( sizeof(PhoneEntry) * 10);
}

int char_compare(void const *a, void const *b){
    return strcmp( ((PhoneEntry*)a)->name,((PhoneEntry*)b)->name );
}

int int_compare(void const *item1, void const *item2){
    int m,n;
    m = ((PhoneEntry*)item1)->number;
    n = ((PhoneEntry*)item2)->number;
    if(m == n) return 0;
    else if(m < n) return -1;
    else return 1;
}

int binarySearch(int l, int r, char *mssv, int *found){
    
    if( bsearch(mssv,A,r-l, sizeof(PhoneEntry),char_compare) == NULL)
        return 0;
    else {
        *found = 1;
        return 1;
    }
}
void import_file(){
    FILE *ptr;
    
    int i = 0,j;
    ptr = fopen("pb.txt", "r");
    if (ptr == NULL)
    {
        printf("Cannot  open the file\n");
        return;
    }
    while (fscanf(ptr, "%d%*c %[^\n]%*c", &A[i].number, A[i].name) == 2)
    {
        i++;
    }
    free(ptr);
    //printf("%d", i);

}


int main()
{
    int j,k = 0, mssv;
    char namee[30];
    initialize();
    import_file();
    printf("\nTRUOC KHI SAP XEP:\n");    
    for(j = 0; j < 6; j++){
        printf("%-20d %-20s\n",A[j].number,A[j].name);
    }
 
    qsort(A, 6, sizeof(PhoneEntry), char_compare);
    printf("\nSAU KHI SAP XEP THEO TEN:\n");
    for(j = 0; j < 6; j++){
        printf("%-20d %-20s\n",A[j].number,A[j].name);
    }
 
    qsort(A, 6 ,sizeof(PhoneEntry), int_compare);
    printf("\nSAU KHI SAP XEP THEO MSSV:\n");
    for(j = 0; j < 6; j++){
        printf("%-20d %-20s\n",A[j].number,A[j].name);
    } 
    /* printf("Nhap mssv: ");
    scanf("%d",&mssv);  
    binarySearch(0,6,&mssv,&k); */
    
    /* printf("Nhap name: ");
    scanf("%s%*c",namee);  
    binarySearch(0,6,namee,&k);

    if(k == 1)  printf("TIM THAY !");
    else printf("KHONG TIM THAY :((("); */

    return 0;
}

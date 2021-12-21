#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10 //The hien so luong ban dau
#define INCREMENTL_SIZE 5 // do tang moi khi can cap pha lai


typedef struct{
    char name[80];
    int number;
} phoneEntry;

typedef struct {
    phoneEntry *entries;
    int total;
    int size;
} phoneBook;


int char_compare(void const *a, void const *b){
    return strcmp( ((phoneEntry*)a)->name, ((phoneEntry*)b)->name );
}

phoneBook createPhoneBook(){ // Ham to danh ba moi
    phoneBook p;
    p.entries = malloc(sizeof(phoneEntry) * INITIAL_SIZE);
    p.total = INITIAL_SIZE;
    p.size = INCREMENTL_SIZE;
    return p;
}

void dropPhoneBook( phoneBook *book){
   // free(book->entries);
}

int binarySearch(phoneEntry *entry, int l, int r, char *name, int *found){
    
    if( bsearch(name,entry,r-l+1, sizeof(phoneEntry),char_compare) == NULL)
        return 0;
    else {
        *found = 1;
        return 1;
    }
}
int main(){
    printf("OK desu\n");
    FILE *ptr;
    phoneBook A = createPhoneBook(); 
    int i = 0,j,k = 0;
    char s[100];
    ptr = fopen("pb.txt", "r");
    if (ptr == NULL)
    {
        printf("Cannot  open the file\n");
        return 1;
    }
    while (fscanf(ptr, "%d%*c %[^\n]%*c", &A.entries[i].number, A.entries[i].name) == 2)
    {
        i++;
    }
    A.total = i - 1;
    A.size = INCREMENTL_SIZE;
    printf("\nTRUOC KHI SAP XEP:\n");    
    for(j = 0; j < 6; j++){
        printf("%-20d %-20s\n",A.entries[j].number,A.entries[j].name);
    }
    free(ptr);
    qsort(A.entries, 6, sizeof(phoneEntry), char_compare);
    printf("\nSAU KHI SAP XEP:\n");    
    for(j = 0; j < 6; j++){
        printf("%-20d %-20s\n",A.entries[j].number,A.entries[j].name);
    }
    printf("Nhap de tim kiem: ");
    scanf("%s%*c",s);
    binarySearch(A.entries,0,A.total,s,&k);
    if(k == 1)  printf("Da tim thay");
    else printf("KHONG TIM THAY");
    return 0;
}
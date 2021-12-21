#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PHONE_NUMBER 1000 // do tang moi khi can cap pha lai

typedef struct
{
    char name[80];
    int number;
} phoneEntry;

typedef struct
{
    phoneEntry entries[MAX_PHONE_NUMBER];
    int total;
} phoneBook;

int char_compare(void const *a, void const *b)
{
    return strcmp(((phoneEntry *)a)->name, ((phoneEntry *)b)->name);
}

/* phoneBook createPhoneBook()
{ // Ham to danh ba moi
    phoneBook p;
    p.entries = malloc(sizeof(phoneEntry) * INITIAL_SIZE);
    p.total = INITIAL_SIZE;
    p.size = INCREMENTL_SIZE;
    return p;
}
 */
/* void dropPhoneBook(phoneBook *book)
{
    // free(book->entries);
}
 */
/* int binarySearch(phoneEntry *entry, int l, int r, char *name, int *found)
{

    if (bsearch(name, entry, r - l + 1, sizeof(phoneEntry), char_compare) == NULL)
        return 0;
    else
    {
        *found = 1;
        return 1;
    }
}
 */
void addPhoneNumber(int number, char *name, phoneBook *book)
{
    int i = 0, k = 0;
    for (i = 0; i < book->total; i++)
    {
        if (strcmp(name, book->entries[i].name) == 0)
        {
            book->entries[i].number = number;
            k = 1;
            break;
        }
    }
    if (k == 0)
    {
        strcpy(book->entries[book->total].name, name);
        book->entries[book->total].number = number;
        (book->total)++;
    }
}
int getPhoneNumber(char *name,phoneBook book){
    int i = 0, k = 0;
    for (i = 0; i < book.total; i++)
    {
        if (strcmp(name, book.entries[i].name) == 0)
        {
            return book.entries[i].number;
        }
    }
    if (k == 0)
    {
        return -1;
    }
}

int main()
{
    FILE *ptr;
    phoneBook A;
    int i = 0, j, k = 0;
    A.total = 0;
    char s[100];
    addPhoneNumber(12345,"Pham Tien Dung",&A);
    addPhoneNumber(12355, "haha",&A);
    for(i = 0; i < A.total;i++){
        printf("%-20s %-20d\n",A.entries[i].name,A.entries[i].number);
    }

    printf("%d",getPhoneNumber("Pham Tien Dung",A));
    /* ptr = fopen("pb.txt", "r");
    if (ptr == NULL)
    {
        printf("Cannot  open the file\n");
        return 1;
    }
    while (fscanf(ptr, "%d%*c %[^\n]%*c", &A.entries[i].number, A.entries[i].name) == 2)
    {
        i++;
    }
 */
    /*  printf("\nTRUOC KHI SAP XEP:\n");    
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
    else printf("KHONG TIM THAY"); */
    return 0;
}
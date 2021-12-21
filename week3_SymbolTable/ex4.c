#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10    //The hien so luong ban dau
#define INCREMENTL_SIZE 10 // do tang moi khi can cap pha lai

typedef struct
{
    char name[80];
    long number;
} phoneEntry;

typedef struct
{
    phoneEntry *entries;
    int total;
    int size;
} phoneBook;

int char_compare(void const *a, void const *b)
{
    return strcmp(((phoneEntry *)a)->name, ((phoneEntry *)b)->name);
}


phoneBook createPhoneBook()
{ // Ham to danh ba moi
    phoneBook p;
    p.entries = malloc(sizeof(phoneEntry) * INITIAL_SIZE);
    p.total = 0 ;
    p.size = INITIAL_SIZE;
    return p;
}

void addPhoneNumber(long number, char *name, phoneBook *book)
{
    if (book->total >= book->size)
    {
        book->entries = (phoneEntry *)realloc(book->entries, sizeof(phoneEntry) * (book->size + INCREMENTL_SIZE));
        book->size += INCREMENTL_SIZE;
    }
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

void dropPhoneBook(phoneBook *book)
{
        free(book->entries);
}
long getPhoneNumber(char *name, phoneBook book)
{
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

long binarySearch(phoneEntry *entry, int l, int r, char *name){
    
    if( bsearch(name,entry,r-l+1, sizeof(phoneEntry),char_compare) == NULL)
        return -1;
    else {
        return entry->number;
    }
}
int main()
{
    phoneBook A = createPhoneBook();
    int i = 0, j, k = 0, choose;
    char c;
    phoneEntry new;

    while (1)
    {
        printf("\n1.Add phone number\n"
               "2.Get phone number\n"
               "3.Display phone number\n"
               "4.Binary search\n"
               "5.Exit\n"
               "--->Choose? ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            printf("Name: ");
            c = getchar();
            gets(new.name);
            printf("Number: ");
            scanf("%ld", &new.number);
            addPhoneNumber(new.number, new.name, &A);
            break;
        case 2:
            printf("Name: ");
            c = getchar();
            gets(new.name);
            if (getPhoneNumber(new.name, A) == -1)
                printf("Khong tim thay !");
            else
                printf("Tim thay !\n%-20s %-20ld\n", new.name, getPhoneNumber(new.name, A));

            break;
        case 3:
            for (j = 0; j < A.total; j++)
            {
                printf("%-20s %-20ld\n", A.entries[j].name, A.entries[j].number);
            }
            break;
        case 4:
            qsort(A.entries, A.total, sizeof(phoneEntry), char_compare);
            printf("Name: ");
            c = getchar();
            gets(new.name);
            if ( binarySearch(A.entries,0, A.total,new.name) == -1)
                printf("Khong tim thay !");
            else
                printf("Tim thay !\n%-20s %-20ld\n", new.name, binarySearch(A.entries,0, A.total,new.name) );

            break;
        case 5:
            dropPhoneBook(&A);
            exit(0);
        default:
            break;
        }
    }

    return 0;
}
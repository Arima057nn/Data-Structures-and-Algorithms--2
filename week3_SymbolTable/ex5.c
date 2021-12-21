#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10    //The hien so luong ban dau
#define INCREMENTL_SIZE 10 // do tang moi khi can cap pha lai

typedef struct
{
    void *key;
    void *value;

} Entry;

typedef struct
{
    Entry *entries;
    int size, total;
    Entry (*makeNode)(void *, void *);
    int (*compare)(void *, void *);
} SympolTable;

int binarySearch(Entry *arr, int l, int r, void *x, int *found, int (*compare)(void *, void *))
{
    if (r < l)
    {
        *found = 0;
        return l;
    }
    int mid = (l + r) / 2;
    int res = compare(x, arr[mid].key);
    if (res == 0)
    {
        *found = 1;
        return mid;
    }
    else if (res < 0)
        return binarySearch(arr, l, mid - 1, x, found, compare);
    else
        return binarySearch(arr, mid + 1, r, x, found, compare);
}

Entry makePhone(void *name, void *phone)
{
    Entry res;
    res.key = strdup((char *)name);
    res.value = malloc(sizeof(int));
    memcpy(res.value, phone, sizeof(int));
    return res;
}
int comparePhone(void *key1, void *key2)
{
    return strcmp((char *)key1, (char *)key2);
}

SympolTable createSymbolTable(Entry(makeNode)(void *, void *), int (*compare)(void *, void *))
{
    SympolTable symtab;
    symtab.entries = (Entry *)malloc(sizeof(Entry) * INITIAL_SIZE);
    symtab.total = 0;
    symtab.size = INITIAL_SIZE;
    symtab.makeNode = makePhone;
    symtab.compare = comparePhone;
    return symtab;
}

void listEntry(SympolTable book)
{
    for (int i = 0; i < book.total; i++)
    {
        printf("%-20s%ln\n", (char *)book.entries[i].key, (long *)(book.entries[i].value));
    }
}

void dropPhoneBook(SympolTable *symtab)
{
    int i;
    for (i = 0; i < symtab->total; i++)
    {
        free(symtab->entries[i].key);
        free(symtab->entries[i].value);
    }
    free(symtab->entries);
}

void addEntry(void *key, void *value, SympolTable *book)
{
    int pos, found;
    if ((*book).total <= 0)
    {
        found = 0;
        pos = 0;
    }
    else
        pos = binarySearch((*book).entries, 0, (*book).total - 1, key, &found, (*book).compare);
    //printf("\t%d", found);
    if (found == 1)
    {
        Entry tmp = (*book).makeNode(key, value);
        memcpy(&(*book).entries[pos], &tmp, sizeof(Entry));
    }
    else
    {
        if ((*book).total >= (*book).size)
        {
            (*book).size += INCREMENTL_SIZE;
            (*book).entries = (Entry *)realloc(book->entries, sizeof(Entry) * (*book).size);
        }
        if (pos < (*book).total)
        {
            memcpy(&((*book).entries[pos + 1]), &((*book).entries[pos]), sizeof(Entry) * ((*book).total - pos));
        }
        (*book).entries[pos] = (*book).makeNode(key, value);
        (*book).total++;
    }
}
Entry *getEntry(void *key, SympolTable symtab)
{
    int i = 0, k = 0;
    for (i = 0; i < symtab.total; i++)
    {
        if (comparePhone(symtab.entries[i].key, key) == 0)
        {
            return symtab.entries;
        }
    }
    if (k == 0)
    {
        return NULL;
    }
}

int main()
{
    SympolTable A = createSymbolTable(makePhone, comparePhone);
    int number = 98398;
    char name[] = "Le Thi Ngoc Huyen";
    addEntry(name, &number, &A);
    addEntry("Pham Tien Dung",232,&A);
    listEntry(A);
    return 0;
}

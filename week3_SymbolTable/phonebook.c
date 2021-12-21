#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

PhoneBook createPhoneBook() {
    PhoneBook p;
    p.entries = malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
    p.total = 0;
    p.size = INITIAL_SIZE;
    return p;
}

void dropPhoneBook(PhoneBook* book) {
  free(book->entries);
}

void addPhoneNumber(char * name, long number, PhoneBook* book) {
  if (book->total >= book->size)
    {
        book->entries = (PhoneEntry *)realloc(book->entries, sizeof(phoneEntry) * (book->size + INCREMENTL_SIZE));
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

PhoneEntry * getPhoneNumber(char * name, PhoneBook book) {
  int i = 0, k = 0;
    for (i = 0; i < book.total; i++)
    {
        if (strcmp(name, book.entries[i].name) == 0)
        {
            return book.entries[i];
        }
    }
    if (k == 0)
    {
        return NULL;
    }
}

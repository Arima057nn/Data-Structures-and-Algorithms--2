#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jval.h"
#include "jrb.h"
#include "fields.h"

typedef struct
{
    char name[100];
    char number[100];
} phonebook;

void insertphonebook(JRB book, char *name, char *number)
{
    jrb_insert_str(book, strdup(name), new_jval_s(strdup(number)));
}

int main()
{
    int x;
    FILE *fin = NULL;
    phonebook tmp;
    JRB book = make_jrb();
    JRB bn;
    char s[20], s2[20];
    while (1)
    {
        printf("1. Import from file\n"
               "2. Traverse book.\n"
               "3. Insert a phone book\n"
               "4. Delete a phone book\n"
               "5. Update phone number\n"
               "6. Exit\n");
        printf("Your choice? ");
        scanf("%d", &x);
        switch (x)
        {
        case 1:
            fin = fopen("phonebook.txt", "r+");
            if (fin == NULL)
            {
                printf("Cannot open file.\n");
                return 1;
            }
            while (fscanf(fin, "%[^\t]%*c%s%*c", tmp.name, tmp.number) == 2)
            {
                printf("%s\t%s\n", tmp.name, tmp.number);
                insertphonebook(book, tmp.name, tmp.number);
            }
            fclose(fin);
            break;
        case 2:
            jrb_traverse(bn, book)
            {
                printf("%s\t%s\n", jval_s(bn->key), jval_s(bn->val));
            }
            break;
        case 3:
            printf("Enter name: ");
            scanf("%[^\n]", tmp.name);
            printf("Enter phone number: ");
            scanf("%[%\n]", tmp.number);

        case 6:
            jrb_free_tree(book);
            exit(0);
            break;
        }
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jval.h"
#include "jrb.h"
#include "fields.h"

typedef struct
{
    char name[50];
    long number;
} phoneBook;

int main()
{
    phoneBook A;
    int choose;
    char c;
    JRB FB = make_jrb();
    JRB fb;
    while (1)
    {

        printf("\n  ==== Menu ====\n"
               "1. Insert a phone book\n"
               "2. Search a phone book\n"
               "3. Delete a phone book\n"
               "4. Update a phone book\n"
               "5. Traverse all phone book\n"
               "6. Exit\n"
               "---> Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            printf("Name: ");
            c = getchar();
            gets(A.name);
            fb = jrb_find_str(FB, strdup(A.name));
            if (fb != NULL)
            {
                printf("Exist\n");
            }
            else
            {
                printf("Number: ");
                scanf("%ld", &A.number);
                jrb_insert_str(FB, strdup(A.name), new_jval_l(A.number));
            }
            break;
        case 2:
            printf("Name: ");
            c = getchar();
            gets(A.name);
            fb = jrb_find_str(FB, strdup(A.name));
            if (fb != NULL)
                printf("%-20s %-20ld\n", jval_s(fb->key), jval_l(fb->val));
            else
                printf("Cannot find\n");
            break;
        case 3:
            printf("Name: ");
            c = getchar();
            gets(A.name);
            fb = jrb_find_str(FB, strdup(A.name));
            if (fb != NULL)
                jrb_delete_node(fb);
            else
                printf("Cannot find\n");
            break;
        case 4: 
            printf("Name: ");
            c = getchar();
            gets(A.name);
            fb = jrb_find_str(FB, strdup(A.name));
            if (fb == NULL)
                printf("Cannot find pb\n");
            else{
                jrb_delete_node(fb);
                printf("number: ");
                scanf("%ld",&A.number);
                jrb_insert_str(FB, strdup(A.name), new_jval_l(A.number));          
                break;          
            }
            break;
        case 5:
            jrb_traverse(fb, FB)
            {
                printf("%-20s %-20ld\n", jval_s(fb->key), jval_l(fb->val));
            }
            break;
        case 6:
            jrb_free_tree(FB);
            exit(0);

        default:
            break;
        }
    }

    return 0;
}


//gcc -I ~/Arima/C_Advance/Library/Libfdr/ -o ex2 ex2.c ~/Arima/C_Advance/Library/Libfdr/libfdr.a

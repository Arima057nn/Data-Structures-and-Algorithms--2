#include <stdio.h>
#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#define MAX 100
typedef struct
{
  char *name;
  char *number;
} phonebook;
int main()
{
  phonebook tmp;
  int x, n, rsize;
  BTA *book;
  btinit();
  char name[] = "conga";
  book = btcrt(name, 0, 0);
  btopn(name, 0, 0);
  tmp.name = malloc(sizeof(char) * MAX);
  tmp.number = malloc(sizeof(char) * MAX);
  while (1)
  {
    printf("1. Them mot thong tin lien lac.\n"
           "2. Hien thi toan bo danh ba.\n"
           "3. Tim kiem theo ten.\n"
           "4. Xoa mot thong tin lien lac\n"
           "5. Thoat.\n");
    printf("Bam chon: ");
    scanf("%d", &x);
    switch (x)
    {
    case 1:
      strcpy(tmp.name, "A");
      strcpy(tmp.number, "A1234567890");
      if (btins(book, strdup(tmp.name), strdup(tmp.number), strlen(tmp.number) + 1) != 0)
      {
        printf("Insert failed.\n");
      }
      strcpy(tmp.name, "B");
      strcpy(tmp.number, "B1234567890");
      if (btins(book, strdup(tmp.name), strdup(tmp.number), strlen(tmp.number) + 1) != 0)
      {
        printf("Insert failed.\n");
      }
      strcpy(tmp.name, "C");
      strcpy(tmp.number, "C1234567890");
      if (btins(book, strdup(tmp.name), strdup(tmp.number), strlen(tmp.number) + 1) != 0)
      {
        printf("Insert failed.\n");
      }
      strcpy(tmp.name, "D");
      strcpy(tmp.number, "D1234567890");
      if (btins(book, strdup(tmp.name), strdup(tmp.number), strlen(tmp.number) + 1) != 0)
      {
        printf("Insert failed.\n");
      }
      printf("Da them thong tin lien lac.\n");
      break;
    case 2:
      btpos(book, 1);
      printf("Display list:\n");
      n = btseln(book, tmp.name, tmp.number, MAX, &rsize);
      while (n != QNOKEY)
      {
        printf("Name: %s Phone number: %s\n", tmp.name, tmp.number);
        n = btseln(book, tmp.name, tmp.number, MAX, &rsize);
      }
      break;
    case 3:
      __fpurge(stdin);
      printf("Nhap ten can tim: ");
      scanf("%[^\n]", tmp.name);
      btpos(book, 1);
      n = btsel(book, tmp.name, tmp.number, MAX, &rsize);
      if (n == 0)
      {
        printf("Phone number: %s\n", tmp.number);
      }
      else
      {
        printf("Not found\n");
      }
      break;
    case 4:
      __fpurge(stdin);
      printf("Nhap ten can xoa: ");
      scanf("%[^\n]", tmp.name);
      n = btsel(book, tmp.name, tmp.number, MAX, &rsize);
      if (n == 0)
      {
        btdel(book, tmp.name);
        printf("Deleted.\n");
      }
      else
      {
        printf("This name is not found.\n");
      }
      break;
    case 5:
      btcls(book);
      exit(0);
      break;
    default:
      break;
    }
  }
}
//gcc -o w6-2 w6-2.c -L./lib -lbt -I./inc

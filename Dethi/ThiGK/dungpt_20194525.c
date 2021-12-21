#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

void print_entry(char *dn, char *ip);
void do_print();
void do_add(char *dn, char *ip);
void do_remove(char *dn);
void do_lookup_ip(char *dn);
void do_lookup_dn(char *ip);

int readFile(FILE *ptr, JRB list);
void freeJRB(JRB list);

int main(int argc, char **argv)
{
  if (argc <= 1)
  {
    printf("Usage: prog print \n       prog add [dn] [ip] \n       prog remove [dn]\n       prog ip [dn]\n       prog dn [ip]\n");
    return 0;
  }

  if (strcmp(argv[1], "print") == 0)
  {
    if (argc != 2)
    {
      printf("Invalid parameters\n");
      return 0;
    }
    do_print();
    return 0;
  }
  if (strcmp(argv[1], "add") == 0)
  {
    if (argc != 4)
    {
      printf("Invalid parameters\n");
      return 0;
    }
    do_add(argv[2], argv[3]);
    return 0;
  }
  if (strcmp(argv[1], "remove") == 0)
  {
    if (argc != 3)
    {
      printf("Invalid parameters\n");
      return 0;
    }
    do_remove(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "ip") == 0)
  {
    if (argc != 3)
    {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_ip(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "dn") == 0)
  {
    if (argc != 3)
    {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_dn(argv[2]);
    return 0;
  }
  printf("Invalid parameters\n");
  return 0;
}

void print_entry(char *dn, char *ip)
{
  printf("%s => %s\n", dn, ip);
}

void freeJRB(JRB list)
{
  JRB p;
  jrb_traverse(p, list)
  {
    free(jval_s(p->key));
    free(jval_s(p->val));
  }

  jrb_free_tree(list);
}

int readFile(FILE *ptr, JRB list)
{
  int n;
  char Name[100], IP[100];
  if (ptr == NULL)
  {
    printf("Error\n");
    exit(0);
  }
  fscanf(ptr, "%d%*c", &n);
  while (fscanf(ptr, "%s%*c%s*c", Name, IP) == 2)
  {
    jrb_insert_str(list, strdup(Name), new_jval_s(strdup(IP)));
  }
  return n;
}

void do_print()
{
  JRB p;
  JRB list = make_jrb();
  FILE *ptr = fopen("dns.txt", "r");
  readFile(ptr, list);
  jrb_traverse(p, list)
  {
    print_entry(jval_s(p->key), jval_s(p->val));
  }
  freeJRB(list);
  fclose(ptr);
}

void do_add(char *dn, char *ip)
{
  JRB p;
  JRB list = make_jrb();
  FILE *ptr = fopen("dns.txt", "r");
  int n = readFile(ptr, list);
  p = jrb_find_str(list, strdup(dn));
  if (p != NULL)
  {
    jrb_delete_node(p);
    jrb_insert_str(list, strdup(dn), new_jval_s(strdup(ip)));
    printf("Complete !\n");
  }
  else
  {
    jrb_insert_str(list, strdup(dn), new_jval_s(strdup(ip)));
    printf("Complete !\n");
    n++;
  }
  fclose(ptr);
  jrb_traverse(p, list)
  {
    print_entry(jval_s(p->key), jval_s(p->val));
  }
  ptr = fopen("dns.txt", "w");
  readFile(ptr, list);
  fprintf(ptr, "%d\n", n);
  jrb_traverse(p, list)
  {
    fprintf(ptr, "%s\n%s\n", jval_s(p->key), jval_s(p->val));
  }

  fclose(ptr);
  freeJRB(list);
}

void do_remove(char *dn)
{
  JRB p;
  JRB list = make_jrb();
  FILE *ptr = fopen("dns.txt", "r");
  int n = readFile(ptr, list);

  p = jrb_find_str(list, strdup(dn));
  if (p != NULL)
  {
    jrb_delete_node(p);
    printf("Complete !\n");
    n--;
  }
  else
  {
    printf("No Exist !\n");
  }
  jrb_traverse(p, list)
  {
    print_entry(jval_s(p->key), jval_s(p->val));
  }
  fclose(ptr);
  ptr = fopen("dns.txt", "w");
  readFile(ptr, list);
  fprintf(ptr, "%d\n", n);
  jrb_traverse(p, list)
  {
    fprintf(ptr, "%s\n%s\n", jval_s(p->key), jval_s(p->val));
  }

  fclose(ptr);
  freeJRB(list);
}

void do_lookup_ip(char *dn)
{
  JRB p;
  JRB list = make_jrb();
  FILE *ptr = fopen("dns.txt", "r");
  int n = readFile(ptr, list);

  p = jrb_find_str(list, strdup(dn));
  if (p != NULL)
  {
    print_entry(dn, jval_s(p->val));
  }
  else
  {
    printf("Not found !\n");
  }
  fclose(ptr);
  freeJRB(list);
}

void do_lookup_dn(char *ip)
{
  JRB p;
  JRB list = make_jrb();
  FILE *ptr = fopen("dns.txt", "r");
  int n = readFile(ptr, list);
  int i = 0;
  jrb_traverse(p, list)
  {
    if (strcmp(ip, jval_s(p->val)) == 0)
    {
      print_entry(jval_s(p->key), ip);
      i++;
    }
  }
  if (i == 0)
    printf("Not found !\n");

  fclose(ptr);
  freeJRB(list);
}

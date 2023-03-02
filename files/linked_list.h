#include "stdbool.h"
#include <stdio.h>

typedef struct Symbol {
  char *name;
  bool is_terminal;
  int row_no;

  struct LinkedList *first;
  struct LinkedList *follow;

  struct Symbol *right;
  // struct Symbol *bottom;

} Symbol;

struct Node {
  struct Node *next;
  Symbol *symbol;
};

typedef struct Node Node;

struct LinkedList {
  Node *head;
  Node *tail;
  int size;
};

typedef struct LinkedList LinkedList;

Node *create_new_node(Symbol *symbol);
LinkedList *create_linked_list();
void insert_node(Symbol *symbol, LinkedList *ll, bool check_if_present);
void print_list(LinkedList *ll, FILE *debug_fp);
void merge_list(LinkedList *l1, LinkedList *l2);
bool find_node(char *name, LinkedList *ll);
void delete_node(char *name, LinkedList *ll);
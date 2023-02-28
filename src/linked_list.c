#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_list(LinkedList *ll) {
  if (ll == NULL || ll->head == NULL) {
    printf("List is empty\n");
    return;
  }
  Node *temp = ll->head;

  // printf("{ ");
  while (temp->next != NULL) {
    printf("%s,", temp->symbol->name);
    temp = temp->next;
  }
  printf("%s\n", temp->symbol->name);
}

Node *create_new_node(Symbol *symbol) {
  Node *new = (Node *)malloc(sizeof(Node *));
  new->next = NULL;
  new->symbol = symbol;
  return new;
}

LinkedList *create_linked_list() {
  LinkedList *ll = (LinkedList *)malloc(sizeof(LinkedList));
  ll->head = NULL;
  ll->tail = NULL;
  ll->size = 0;
  return ll;
}

bool find_node(char *name, LinkedList *ll) {
  Node *temp = ll->head;

  while (temp != NULL) {
    if (strcmp(temp->symbol->name, name) == 0) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

void insert_node(Symbol *symbol, LinkedList *ll, bool check_if_present) {
  if (check_if_present && find_node(symbol->name, ll))
    return;

  Node *new = create_new_node(symbol);

  if (ll->head == NULL) {
    ll->head = new;
  } else {
    // insert the node at the beginning of the list.
    new->next = ll->head;
    ll->head = new;
  }

  ll->size++;
}

void merge_list(LinkedList *l1, LinkedList *l2) {
  if (l2 == NULL)
    return;

  Node *temp = l2->head;
  while (temp != NULL) {
    insert_node(temp->symbol, l1, true);
    temp = temp->next;
  }
  l1->size += l2->size;
}

void delete_node(char *name, LinkedList *ll) {
  Node *fast = ll->head;
  Node *slow = ll->head;

  if (strcmp(fast->symbol->name, name) == 0) {
    ll->head = ll->head->next;
    ll->size--;
    return;
  }

  fast = fast->next;

  while (fast != NULL) {
    if (strcmp(fast->symbol->name, name) == 0) {
      // remove kardo isko bhencho.
      slow->next = fast->next;
      free(fast);
      return;
    }
    fast = fast->next;
    slow = slow->next;
  }
}

int get_length(Symbol *Rule){
    int length = 0;
    Symbol *curr = Rule;
    while (curr != NULL){
        length++;
        curr = curr->right;
    }
    return length;
}

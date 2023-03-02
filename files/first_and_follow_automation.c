#include "linked_list.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GRAMMAR_SIZE = 0;
int RULE_WIDTH = 512;
int TOTAL_SYMBOLS = 0;
int MAX_SYMBOLS_ARRAY_SIZE = 64;
char **grammar;
Symbol *symbols[256];

char **read_file(char *file) {
  int ROW_TOTAL = 16;
  int COL_TOTAL = 128;
  char **array;

  array = (char **)malloc(ROW_TOTAL * sizeof(char *)); // 4
  for (int i = 0; i < ROW_TOTAL; i++)
    array[i] = (char *)malloc(COL_TOTAL * sizeof(char)); // 32

  FILE *fp;
  fp = fopen(file, "r");
  if (fp != NULL) {
    char buff[1024];
    while (fgets(buff, 1024, fp)) {
      int size_row = COL_TOTAL;
      int col_no = 0;

      char *tok = strtok(buff, "\n");
      if (tok == NULL)
        break;
      int size = (strlen(tok) + 2);
      char *memory = (char *)malloc(size * sizeof(char));
      strcpy(memory, tok);
      memory[size - 2] = ' ';
      memory[size - 1] = '\0';
      array[GRAMMAR_SIZE] = memory;
      GRAMMAR_SIZE++;
    }

  } else {
    printf("Failed to open file!\n");
    exit(EXIT_FAILURE);
  }

  return array;
}

void print_symbol_details(Symbol *s) {
  printf("Name: %s, ", s->name);
  printf("%s\n", s->is_terminal ? "Terminal" : "Non Terminal");
  printf("First: ");
  print_list(s->first);
  printf("Follow: ");
  print_list(s->follow);

  printf("Right: [HEAD] -> ");

  Symbol *temp = s->right;
  while (temp != NULL) {
    printf("%s -> ", temp->name);
    temp = temp->right;
  }
  printf("[END]\n");

  printf("Row no: %d\n", s->row_no);
  printf("\n");
}

// Assuming that the terminal or non terminal length in the grammar will not
// exceed 32 characters ever.

LinkedList *compute_first(Symbol *curr) {
  LinkedList *ll = create_linked_list();
  if (curr == NULL)
    return ll;

  if (curr->is_terminal) {
    insert_node(curr, ll);
    return ll;
  }

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    if (strcmp(symbols[i]->name, curr->name) == 0) {
      // printf("Sending: %s", curr->right->name);
      Symbol *temp = symbols[i]->right;
      // printf("%s : ", temp->name);

      while (temp != NULL) {
        LinkedList *first = compute_first(temp);
        // print_list(first);
        merge_list(ll, first);
        printf("after merge\n");

        if (!find_node("#", ll))
          break;

        printf("after find node statement\n");

        if (temp->right != NULL)
          delete_node("#", ll);
        printf("after temp right not null statement\n");

        temp = temp->right;
      }
    }
  }

  return ll;
}

LinkedList *compute_follow(Symbol *curr) {
  LinkedList *ll = create_linked_list();
  if (curr == NULL)
    return ll;

  if (curr->is_terminal) {
    insert_node(curr, ll);
    return ll;
  }

  // printf("Scanning: %s\n", curr->name);

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    Symbol *temp = symbols[i]->right;
    // printf("Seg fault may be due to total symbols : %s\n", symbols[i]->name);

    while (temp != NULL) {
      if (strcmp(temp->name, curr->name) == 0) {
        if (temp->right == NULL && strcmp(symbols[i]->name, curr->name) != 0) {
          merge_list(ll, compute_follow(symbols[i]));
        } else {
          merge_list(ll, compute_first(temp->right));
        }
      }
      temp = temp->right;
    }
  }
  return ll;
}

void build_grammar() {
  // grammar = read_file("dummy_grammar1.txt");
  grammar = read_file("grammar.txt");
  //
  printf("%d", GRAMMAR_SIZE);

  for (int i = 0; i < GRAMMAR_SIZE; i++) {
    printf("%s\n", grammar[i]);
  }

  // find symbols from this.
  Symbol *prev = NULL;
  for (int i = 0; i < GRAMMAR_SIZE; i++) {
    int j = 0;
    int sz = 0;
    int symbols_for_current_row = 0;

    char symbol_name[32] = {'@'};
    while (grammar[i][j] != '\0') {
      if (!isspace(grammar[i][j])) {
        symbol_name[sz] = grammar[i][j];
        sz++;
      } else {
        if (symbol_name[0] == '=') {
          sz = 0;
          j++;
          continue;
        }

        Symbol *new = (Symbol *)malloc(sizeof(Symbol));

        new->name = (char *)malloc(sz * sizeof(char));
        for (int k = 0; k < sz; k++)
          new->name[k] = symbol_name[k];

        // need to create the linked list first.
        new->first = create_linked_list();
        new->follow = create_linked_list();
        new->row_no = i;

        if (prev != NULL && prev->row_no == new->row_no) {
          prev->right = new;
        }

        if (isupper(symbol_name[0]))
          new->is_terminal = false;
        else
          new->is_terminal = true;

        prev = new;
        // TODO: Do dynamic memory allocation here.

        if (symbols_for_current_row == 0) {
          symbols_for_current_row++;
          symbols[TOTAL_SYMBOLS] = new;
          TOTAL_SYMBOLS++;
        }
        sz = 0;
      }
      j++;
    }
    symbols_for_current_row = 0;
  }
}
Symbol **generate_parse_table() {
  // generates the parse table required for the parsing process of the compiler.

  // array of first and follows.
  LinkedList *data[TOTAL_SYMBOLS];

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    Symbol *temp = symbols[i]->right;
    data[i] = create_linked_list();

    while (temp != NULL) {
      temp->first = compute_first(temp);

      merge_list(data[i], temp->first);

      if (!find_node("#", data[i]))
        break;

      if (temp->right != NULL)
        delete_node("#", temp->first);
      temp = temp->right;
    }

    if (find_node("#", data[i])) {
      LinkedList *ret = compute_follow(symbols[i]);
      merge_list(data[i], ret);
      delete_node("#", data[i]);
    }
  }

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    printf("%s: ", symbols[i]->name);
    print_list(data[i]);
  }

  return NULL;
}

int main() {
  // automate_first_follow();
  build_grammar();
  generate_parse_table();
  free(grammar);
  return 0;
}
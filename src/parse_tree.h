#include "linked_list.c"
#include "stdbool.h"

typedef struct TreeNode {
  struct TreeNode *parent;
  struct TreeNode *head;
  struct TreeNode *tail;
  struct TreeNode *sibling;
  struct Symbol *symbol;
} TreeNode;

void read_grammar_file(char *file);
void print_symbol_details(Symbol *s, FILE *debug_fp);
void print_symbol_info(Symbol *s, FILE *debug_fp);
void build_grammar(char *grammar_file);
LinkedList *compute_first(Symbol *curr);
LinkedList *compute_follow(Symbol *curr);
void generate_parse_table();
void print_parse_table();
void parse_table_make();
void update_NT_ROWS();

TreeNode *create_parse_tree();
TreeNode *create_treeNode();
void insert_child(TreeNode *parent,
                  Symbol *symbol); // pointer to parent, and LHS of grammar
void print_terminal_list();
/* typedef struct LinkedList LinkedList; */

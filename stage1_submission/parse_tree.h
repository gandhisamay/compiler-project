/*
 * Group 22
 * Samay Gandhi 2020A7PS0299P
 * Mohit Makwana 2020A7PS0048P
 * Kathan Patel 2020A7PS0058P
 * Aditya Sheth 2020A7PS1511P
 * Aryan Chavan 2020A7PS1692P
 */

#include "linked_list.c"
#include "stdbool.h"

typedef struct TreeNode {
  struct TreeNode *parent;
  struct TreeNode *head;
  struct TreeNode *tail;
  struct TreeNode *sibling;
  struct Symbol *symbol;
  struct TreeNode* node_syn;
  struct TreeNode* node_inh;
  struct TreeNode* list_head_syn;
  struct TreeNode* list_tail_syn;
  struct TreeNode* list_sib_syn;
  struct TreeNode* list_head_inh;
  struct TreeNode* list_tail_inh;
  struct TreeNode* list_sib_inh;
  bool visited;
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

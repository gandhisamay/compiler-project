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

typedef struct ast_node
{
    char label[200];
    struct ast_node *head;
    struct ast_node *tail;
    struct ast_node *sibling;
    struct ast_node *parent;
    Symbol *data;
} AST_NODE;

typedef struct TreeNode {
  struct TreeNode *parent;
  struct TreeNode *head;
  struct TreeNode *tail;
  struct TreeNode *sibling;
  struct Symbol *symbol;
  AST_NODE *node_syn;
  AST_NODE *node_inh;
  AST_NODE* list_head_syn;
  AST_NODE* list_tail_syn;
  AST_NODE* list_sib_syn;
  AST_NODE* list_head_inh;
  AST_NODE* list_tail_inh;
  AST_NODE* list_sib_inh;
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

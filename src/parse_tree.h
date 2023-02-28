#include "linked_list.c"
#include "stdbool.h"

typedef struct TreeNode{
    struct TreeNode* parent;
    struct TreeNode* head;
    struct TreeNode* tail;
    struct TreeNode* sibling;
    struct Symbol *symbol;
} TreeNode;

int GRAMMAR_SIZE = 0;
int RULE_WIDTH = 512;
int TOTAL_SYMBOLS = 0;
int MAX_SYMBOLS_ARRAY_SIZE = 64;
char **grammar;
Symbol *symbols[256];
LinkedList **data;
Symbol*** parser_table;


TreeNode* ParseTree;

char **read_grammar_file(char *file); 
void print_symbol_details(Symbol *s, FILE* debug_fp);
void build_grammar(char *grammar_file);
LinkedList *compute_first(Symbol *curr);
LinkedList *compute_follow(Symbol *curr);
Symbol **generate_parse_table();
void print_parse_table();
void parse_table_make();

TreeNode* create_parse_tree();
TreeNode* create_treeNode();
TreeNode* insert_child(TreeNode* parent, Symbol *symbol); // pointer to parent, and LHS of grammar
void print_terminal_list();
/* typedef struct LinkedList LinkedList; */

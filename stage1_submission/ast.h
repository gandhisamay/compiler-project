#include "symbol_table.c"

// TreeNode *create_tree_node_AST(TreeNode *syn_node, TreeNode *inh_node, TreeNode *syn_list, TreeNode *inh_list);
// AST_NODE *insert_at_head_syn(TreeNode *list_head, AST_NODE *node);
// AST_NODE *insert_at_head_inh(TreeNode *list_head, AST_NODE *node);
// AST_NODE *insert_at_end_syn(TreeNode *list_tail, AST_NODE *node);
// AST_NODE *insert_at_end_inh(TreeNode *list_tail, AST_NODE *node);
// AST_NODE *create_AST_node(char *label);
// AST_NODE *insert_ast_node_head(AST_NODE *parent, AST_NODE *node);
// AST_NODE *insert_ast_node_tail(AST_NODE *parent, AST_NODE *node);
/* void run_ast(char *prog_file, char *output_file); */
/* void resolve(TreeNode *node); */

typedef struct Scope{
    int start_line;
    int end_line;
    char module_name[50];
    bool is_a_module;
    int iplist_offset;
    int oplist_offset;
    struct Scope *child_scope;
    struct Scope *sibling_scope;
    struct Scope *parent_scope;
    SYMBOL_TABLE_ELEMENT* table[SYMB_SIZE];
} Scope;

Scope *GLOBAL_SCOPE;
int CURR_OFFSET = 0;
bool TYPE_CHECKING = false;

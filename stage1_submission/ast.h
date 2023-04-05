#include "parser.c"


TreeNode* create_tree_node_AST(TreeNode* syn_node, TreeNode* inh_node, TreeNode* syn_list, TreeNode* inh_list);
TreeNode* insert_at_head_syn(TreeNode* list_head, TreeNode* node);
TreeNode* insert_at_head_inh(TreeNode* list_head, TreeNode* node);
TreeNode* insert_at_end_syn(TreeNode* list_tail, TreeNode* node);
TreeNode* insert_at_end_inh(TreeNode* list_tail, TreeNode* node);
AST_NODE *create_AST_node(char *label);
AST_NODE *insert_ast_node_head(AST_NODE *parent, AST_NODE *node);
AST_NODE *insert_ast_node_tail(AST_NODE *parent, AST_NODE *node);
void run_ast(char *prog_file, char *output_file);
void resolve(TreeNode *node);

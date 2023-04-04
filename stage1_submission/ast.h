#include "parser.c"


TreeNode* create_AST_node(TreeNode* syn_node, TreeNode* inh_node, TreeNode* syn_list, TreeNode* inh_list);
TreeNode* insert_at_head_syn(TreeNode* list_head, TreeNode* node);
TreeNode* insert_at_head_inh(TreeNode* list_head, TreeNode* node);
TreeNode* insert_at_end_syn(TreeNode* list_tail, TreeNode* node);
TreeNode* insert_at_end_inh(TreeNode* list_tail, TreeNode* node);
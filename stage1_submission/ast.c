#include "ast.h"


TreeNode* create_AST_node(TreeNode* syn_node, TreeNode* inh_node, TreeNode* syn_list, TreeNode* inh_list){
    TreeNode* new_node = create_treeNode();
    new_node->node_syn = syn_node;
    new_node->node_inh = inh_node;
    new_node->list_head_syn = syn_list;
    new_node->list_head_inh = inh_list;
    return new_node;
}

TreeNode* insert_at_head_syn(TreeNode* list_head, TreeNode* node){
    node->list_sib_syn = list_head;
    list_head->list_head_syn = node;
}

TreeNode* insert_at_head_inh(TreeNode* list_head, TreeNode* node){
    node->list_sib_inh = list_head;
    list_head->list_head_inh = node;
}

TreeNode* insert_at_end_syn(TreeNode* list_tail, TreeNode* node){
    
}

TreeNode* insert_at_end_inh(TreeNode* list_tail, TreeNode* node){
    
}

TreeNode* copy_tree(TreeNode* root, TreeNode* new_root){

    /* printf(">> HERE \n"); */
    if (root != NULL) {
    copy_tree(root->head,new_root->head);

    // fprintf(outfile, "==============>  ");
    // print_symbol_details(root->symbol, outfile);
    new_root->symbol = root->symbol;
    // fprintf(outfile, "\n\n");

    if (root->head != NULL) {
      TreeNode *curr = root->head;
      TreeNode* new_curr = create_treeNode();
      curr = curr->sibling;
      if(curr->sibling!=NULL){
        new_curr->sibling = create_treeNode();
      }

      while (curr != NULL) {
        copy_tree(curr, new_curr);
        if(curr->sibling!=NULL){
            new_curr->sibling = create_treeNode();
        }
        curr = curr->sibling;
        new_curr = new_curr->sibling;
      }
    }
  }
}

void run_ast(char* prog_file, char* output_file){
    run_parser(prog_file,output_file);
    TreeNode* AST_root = Parse_Tree_Root;
    printParseTree(AST_root, stdout);
    printf("SDfsdfds\n");
    print_astnode_details(AST_root, stdout);
    TreeNode *tmp = AST_root->head;
    while (tmp != NULL){
        print_astnode_details(tmp, stdout);
        tmp = tmp->sibling;
    }
}

void resolve(TreeNode *node){
    if (node->symbol->is_terminal){

    } else {
        if (node->symbol->non_terminal == Program){
            resolve(node->head->sibling->sibling);
            node->node_syn = node->head->sibling->sibling->node_syn;
        }
        else if (node->symbol->non_terminal == DriverModule){
            resolve(node->tail);
            node->node_syn = node->tail->node_syn;
        }
    }
}

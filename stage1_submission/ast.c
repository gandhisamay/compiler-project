#include "ast.h"

typedef struct ast_node
{
    char label[200];
    struct ast_node *head;
    struct ast_node *tail;
    struct ast_node *sibling;
    struct ast_node *parent;
    TreeNode *data;
} AST_NODE;

TreeNode *create_tree_node_AST(TreeNode *syn_node, TreeNode *inh_node, TreeNode *syn_list, TreeNode *inh_list)
{
    TreeNode *new_node = create_treeNode();
    new_node->node_syn = syn_node;
    new_node->node_inh = inh_node;
    new_node->list_head_syn = syn_list;
    new_node->list_head_inh = inh_list;
    return new_node;
}

TreeNode *insert_at_head_syn(TreeNode *list_head, TreeNode *node)
{
    node->list_sib_syn = list_head;
    list_head->list_head_syn = node;
    if (node->list_tail_syn == NULL)
        list_head->list_tail_syn = node;
}

TreeNode *insert_at_head_inh(TreeNode *list_head, TreeNode *node)
{
    node->list_sib_inh = list_head;
    list_head->list_head_inh = node;
    if (node->list_tail_inh == NULL)
        list_head->list_tail_inh = node;
}

TreeNode *insert_at_end_syn(TreeNode *list_tail, TreeNode *node)
{
}

TreeNode *insert_at_end_inh(TreeNode *list_tail, TreeNode *node)
{
}

AST_NODE *create_AST_node(char *label)
{
    AST_NODE *node = (AST_NODE *)malloc(sizeof(AST_NODE));
    strcpy(node->label, label);
    return node;
}

AST_NODE *insert_ast_node_head(AST_NODE *parent, AST_NODE *node)
{
    node->sibling = parent->head;
    parent->head = node;
    if (parent->tail == NULL)
        parent->tail = node;
}

AST_NODE *insert_ast_node_tail(AST_NODE *parent, AST_NODE *node)
{
    if (parent->head == NULL)
    {
        parent->head = node;
        parent->tail = node;
    }
    else
    {
        parent->tail->sibling = node;
        parent->tail = node;
    }
}
// TreeNode* copy_tree(TreeNode* root, TreeNode* new_root){

//     /* printf(">> HERE \n"); */
//     if (root != NULL) {
//     copy_tree(root->head,new_root->head);

//     // fprintf(outfile, "==============>  ");
//     // print_symbol_details(root->symbol, outfile);
//     new_root->symbol = root->symbol;
//     // fprintf(outfile, "\n\n");

//     if (root->head != NULL) {
//       TreeNode *curr = root->head;
//       TreeNode* new_curr = create_treeNode();
//       curr = curr->sibling;
//       if(curr->sibling!=NULL){
//         new_curr->sibling = create_treeNode();
//       }

//       while (curr != NULL) {
//         copy_tree(curr, new_curr);
//         if(curr->sibling!=NULL){
//             new_curr->sibling = create_treeNode();
//         }
//         curr = curr->sibling;
//         new_curr = new_curr->sibling;
//       }
//     }
//   }
// }

void run_ast(char *prog_file, char *output_file)
{
    run_parser(prog_file, output_file);
    AST_NODE *AST_ROOT = create_AST_node("MAINPROGRAM");
    resolve(AST_ROOT, Parse_Tree_Root->head->sibling->sibling);
}

void resolve(AST_NODE *parent, AST_NODE *node)
{
    if (node->symbol->is_terminal)
    {
    }
    else
    {
        if (node->symbol->non_terminal == Program)
        {
            /* resolve(node->head->sibling->sibling); */
            /* node->node_syn = node->head->sibling->sibling->node_syn; */
            // throw error
        }
        else if (node->symbol->non_terminal == DriverModule)
        {
            AST_NODE *DRIVER = create_AST_node("DRIVER");
            resolve(node->tail); // ModuleDef
            insert_ast_node_tail(DRIVER, node->tail->node_syn);
            node->node_syn = DRIVER;
            insert_ast_node_tail(parent, node->node_syn);
        }
        else if (node->symbol->non_terminal == ModuleDef){
            AST_NODE *STATEMENTS = create_AST_node("STATEMENTS");
            resolve(node->head->sibling); // Statements
            AST_NODE *tmp = node->head->sibling->list_head_syn;
            while (tmp != NULL){
                insert_ast_node_tail(STATEMENTS, tmp);
                tmp = tmp->sibling;
            }
            node->node_syn = STATEMENTS;
        }
    }
}

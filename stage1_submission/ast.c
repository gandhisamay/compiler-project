#include "ast.h"

TreeNode *create_tree_node_AST(TreeNode *syn_node, TreeNode *inh_node, TreeNode *syn_list, TreeNode *inh_list)
{
    TreeNode *new_node = create_treeNode();
    new_node->node_syn = syn_node;
    new_node->node_inh = inh_node;
    new_node->list_head_syn = syn_list;
    new_node->list_head_inh = inh_list;
    return new_node;
}

AST_NODE *insert_at_head_syn(TreeNode *list_head, AST_NODE *node)
{
    node->sibling = list_head;
    list_head->list_head_syn = node;
    if (list_head->list_tail_syn == NULL)
        list_head->list_tail_syn = node;
}

AST_NODE *insert_at_head_inh(TreeNode *list_head, AST_NODE *node)
{
    node->sibling = list_head;
    list_head->list_head_inh = node;
    if (list_head->list_tail_inh == NULL)
        list_head->list_tail_inh = node;
}

AST_NODE *insert_at_end_syn(TreeNode *list_tail, AST_NODE *node)
{
    if(list_tail->list_tail_syn == NULL) {
        list_tail->list_head_syn = node;
        list_tail->list_tail_syn = node;
    }
    else{
        list_tail->list_tail_syn->sibling = node;
        list_tail->list_tail_syn = node;
    }

}

AST_NODE *insert_at_end_inh(TreeNode *list_tail, AST_NODE *node)
{
    if(list_tail->list_tail_inh == NULL) {
        list_tail->list_head_inh = node;
        list_tail->list_tail_inh = node;
    }
    else{
        list_tail->list_tail_inh->sibling = node;
        list_tail->list_tail_inh = node;
    }
}

AST_NODE *create_AST_node(char *label)
{
    AST_NODE *node = (AST_NODE *)malloc(sizeof(AST_NODE));
    strcpy(node->label, label);
    node->head = NULL;
    node->tail = NULL;
    node->sibling = NULL;
    node->data = NULL;
    node->parent = NULL;
    return node;
}

AST_NODE *insert_ast_node_head(AST_NODE *parent, AST_NODE *node)
{
    node->sibling = parent->head;
    parent->head = node;
    node->parent = parent;
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
    node->parent = parent;
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

void resolve(AST_NODE *parent, TreeNode *node)
{
    print_astnode_details(parent, stdout);
    print_symbol_details(node->symbol, stdout);
    if (node->symbol->is_terminal)
    {
        if (node->symbol->terminal == iD)
        {
            AST_NODE *ast_id = create_AST_node("iD");
            ast_id->data = node->symbol;
            node->node_syn = ast_id;
            print_astnode_details(node->node_syn, stdout);
        }
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
            resolve(NULL, node->tail); // ModuleDef
            insert_ast_node_tail(DRIVER, node->tail->node_syn);
            node->node_syn = DRIVER;
            insert_ast_node_tail(parent, node->node_syn);
        }
        else if (node->symbol->non_terminal == ModuleDef)
        {
            AST_NODE *STATEMENTS = create_AST_node("STATEMENTS");
            resolve(STATEMENTS, node->head->sibling); // Statements
            /* AST_NODE *tmp = node->head->sibling->list_head_syn; */
            /* while (tmp != NULL){ */
            /*     insert_ast_node_tail(STATEMENTS, tmp); */
            /*     tmp = tmp->sibling; */
            /* } */
            node->node_syn = STATEMENTS;
            insert_ast_node_tail(parent, node->node_syn);
        }
        else if (node->symbol->non_terminal == Statements)
        {
            if (node->head->sibling == NULL)
            { // Statements => #
                node->list_head_syn = NULL;
            }
            else
            {
                printf("\nStatements data\n");
                resolve(NULL, node->tail); // Statements1
                resolve(NULL, node->head); // Statement
                node->list_head_syn = node->tail->list_head_syn;
                printf("sfdsfds1\n");
                /* insert_ast_node_head(node->list_head_syn, node->head->node_syn); */
                insert_at_head_syn(node, node->head->node_syn);
                printf("sfdsfds2\n");
                AST_NODE *tmp = node->list_head_syn;
                printf("\nStatements data\n");
                while (tmp != NULL)
                {
                    print_astnode_details(tmp, stdout);
                    tmp = tmp->sibling;
                }
            }
            if (parent != NULL)
            {
                AST_NODE *tmp = node->list_head_syn;
                while (tmp != NULL)
                {
                    insert_ast_node_tail(parent, tmp);
                    tmp = tmp->sibling;
                }
            }
        }
        else if (node->symbol->non_terminal == Statement)
        {
            resolve(NULL, node->head);
            node->node_syn = node->head->node_syn;
            print_astnode_details(node->node_syn, stdout);
            /* if (node->head->symbol == IoStmt){ */
            /*  */
            /* } else if (node->head->symbol == SimpleStmt){ */
            /*  */
            /* } else if (node->head->symbol == DeclareStmt){ */
            /*  */
            /* } else if (node->head->symbol == ConditionalStmt){ */
            /*  */
            /* } else if (node->head->symbol == IterativeStmt){ */
            /*  */
            /* } */
        }
        else if (node->symbol->non_terminal == IoStmt)
        {
            if (node->head->symbol->terminal == pRINT)
            {
                AST_NODE *PRINT = create_AST_node("PRINT");
                node->node_syn = PRINT;
                resolve(NULL, node->head->sibling->sibling);
                insert_ast_node_head(node->node_syn, node->head->sibling->sibling->node_syn);
            }
            else
            {
                AST_NODE *GET_VALUE = create_AST_node("GET_VALUE");
                node->node_syn = GET_VALUE;
                resolve(NULL, node->head->sibling->sibling);
                node->node_syn = node->head->sibling->sibling->node_syn;
                print_astnode_details(node->node_syn, stdout);
            }
        }
    }
}

void run_ast(char *prog_file, char *output_file)
{
    run_parser(prog_file, output_file);
    AST_NODE *AST_ROOT = create_AST_node("MAINPROGRAM");
    resolve(AST_ROOT, Parse_Tree_Root->head->head->sibling->sibling);
}

#include "ast.h"

// TreeNode *create_tree_node_AST(TreeNode *syn_node, TreeNode *inh_node, TreeNode *syn_list, TreeNode *inh_list)
// {
//     TreeNode *new_node = create_treeNode();
//     new_node->node_syn = syn_node;
//     new_node->node_inh = inh_node;
//     new_node->list_head_syn = syn_list;
//     new_node->list_head_inh = inh_list;
//     return new_node;
// }

// AST_NODE *insert_at_head_syn(TreeNode *list_head, AST_NODE *node)
// {
//     node->sibling = list_head->list_head_syn;
//     list_head->list_head_syn = node;
//     if (list_head->list_tail_syn == NULL)
//         list_head->list_tail_syn = node;
// }

// AST_NODE *insert_at_head_inh(TreeNode *list_head, AST_NODE *node)
// {
//     AST_NODE* temp = node;
//     while(node->sibling != NULL){
//         node = node->sibling;
//     }
//     node->sibling = list_head->list_head_inh;
//     list_head->list_head_inh = temp;
//     if (list_head->list_tail_inh == NULL)
//         list_head->list_tail_inh = node;
//     free(temp);
// }

// AST_NODE *insert_at_end_syn(TreeNode *list_tail, AST_NODE *node)
// {
//     if(list_tail->list_tail_syn == NULL) {
//         list_tail->list_head_syn = node;

//     }
//     else{
//         list_tail->list_tail_syn->sibling = node;

//     }
//     while(node->sibling != NULL){
//         node = node->sibling;
//     }
//     list_tail->list_tail_syn = node;

// }

// AST_NODE *insert_at_end_inh(TreeNode *list_tail, AST_NODE *node)
// {
//     if(list_tail->list_tail_inh == NULL) {
//         list_tail->list_head_inh = node;

//     }
//     else{
//         list_tail->list_tail_inh->sibling = node;

//     }
//     while(node->sibling != NULL){
//         node = node->sibling;
//     }
//     list_tail->list_tail_inh = node;
// }

// AST_NODE *create_AST_node(char *label)
// {
//     AST_NODE *node = (AST_NODE *)malloc(sizeof(AST_NODE));
//     strcpy(node->label, label);
//     node->head = NULL;
//     node->tail = NULL;
//     node->sibling = NULL;
//     node->data = NULL;
//     node->parent = NULL;
//     return node;
// }

// AST_NODE *insert_ast_node_head(AST_NODE *parent, AST_NODE *node)
// {
//     AST_NODE* temp = node;
//     while(node->sibling != NULL){
//         node = node->sibling;
//     }
//     node->sibling = parent->head;
//     parent->head = temp;
//     temp->parent = parent;
//     if (parent->tail == NULL)
//         parent->tail = node;
//     while(temp->sibling != NULL){
//         temp->parent = parent;
//         temp = temp->sibling;
//     }
//     free(temp);
// }

// AST_NODE *insert_ast_node_tail(AST_NODE *parent, AST_NODE *node)
// {
//     if (parent->head == NULL)
//     {
//         parent->head = node;

//     }
//     else
//     {
//         parent->tail->sibling = node;

//     }
//     node->parent = parent;
//     while(node->sibling != NULL){
//         node->parent = parent;
//         node = node->sibling;
//     }
//     parent->tail = node;
// }
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

AST_NODE *create_AST_node(char *label, Symbol *data){
    AST_NODE *node = (AST_NODE *)malloc(sizeof(AST_NODE));
    /* AST_NODE *node = (AST_NODE *)malloc(sizeof(AST_NODE *)); */
    strcpy(node->label, label);
    node->data = data;
    node->sibling = NULL;
    return node;
}

AST_NODE *copy_AST_node(AST_NODE *node){
    AST_NODE *tmp = create_AST_node(node->label, node->data);
    /* tmp->sibling = node->sibling; */
    return tmp;
}

void insert_AST_head(TreeNode *treenode, AST_NODE *astnode) {
    AST_NODE *tmp = astnode;
    while (tmp->sibling != NULL){
        tmp = tmp->sibling;
    }
    if (treenode->list_head == NULL){
        treenode->list_head = astnode;
        treenode->list_tail = tmp;
        /* while (astnode->sibling != NULL){ */
        /*     astnode = astnode->sibling; */
        /* } */
        /* treenode->list_tail = astnode; */
    } else {
        tmp->sibling = treenode->list_head;
        treenode->list_head = astnode;
        printf("\nCHECK %b %b\n", treenode->list_head->sibling == NULL, treenode->list_head->sibling->sibling == NULL);
    }
    /* AST_NODE *temp = copy_AST_node(astnode); */
    /* while (temp->sibling != NULL){ */
    /*     temp = temp->sibling; */
    /* } */
    /* temp->sibling = treenode->list_head; */
    /* treenode->list_head = astnode; */
    /* if (treenode->list_tail == NULL) */
    /*     treenode->list_tail = temp; */
    /* free(temp); */
}

void print_astnodes(TreeNode *node){
    AST_NODE *tmp = node->list_head;
    while (tmp != NULL){
        print_astnode_details(tmp, stdout);
        tmp = tmp->sibling;
    }
}

void insert_AST_tail(TreeNode *treenode, AST_NODE *astnode) {
    if (treenode->list_tail == NULL){
        treenode->list_head = astnode;
        treenode->list_tail = astnode;
    } else {
        AST_NODE *tmp = treenode->list_tail;
        printf("\nIN\n");
        AST_NODE *temp = copy_AST_node(astnode);
        treenode->list_tail->sibling = temp;
        /* printf("CHECK %b %b %b %b\n", temp == NULL, treenode->list_tail->sibling == temp, treenode->list_head->sibling == NULL, treenode->list_tail->sibling == NULL); */
        while (tmp->sibling != NULL){
            tmp = tmp->sibling;
        }
        treenode->list_tail = tmp;
    }
    print_astnodes(treenode);
    printf("\nOUT\n");
}

void resolve(TreeNode *node) {
    /* print_symbol_details(node->symbol, stdout); */
    printf("\n>>>HERE\n");
    if (node->symbol->is_terminal){
        if (node->symbol->terminal == iD){
            AST_NODE *ast_id = create_AST_node("iD", node->symbol);
            ast_id->data = node->symbol;
            insert_AST_head(node, ast_id);
            print_astnodes(node);
        }
    }
    else {
        if (node->symbol->non_terminal == Program){
            /* resolve(node->head->sibling->sibling); */
            /* node->node_syn = node->head->sibling->sibling->node_syn; */
            // throw error
        }
        else if (node->symbol->non_terminal == DriverModule){
            AST_NODE *DRIVER = create_AST_node("DRIVER", NULL);
            insert_AST_head(node, DRIVER);
            resolve(node->tail); // ModuleDef
            DRIVER->sibling = node->tail->list_head;
            print_astnodes(node);
        }
        else if (node->symbol->non_terminal == ModuleDef){
            AST_NODE *STATEMENTS = create_AST_node("STATEMENTS", NULL);
            insert_AST_head(node, STATEMENTS);
            resolve(node->head->sibling); // Statements
            STATEMENTS->sibling = node->head->sibling->list_head;
            print_astnodes(node);
            /* AST_NODE *tmp = node->node_syn; */
            /* while (tmp != NULL) */
            /* { */
            /*     print_astnode_details(tmp, stdout); */
            /*     tmp = tmp->sibling; */
            /* } */
        }
        else if (node->symbol->non_terminal == Statements){
            if (node->head->sibling == NULL){ // Statements => #
                node->list_head = NULL;
            } else {
                resolve(node->tail); // Statements1
                resolve(node->head); // Statement
                node->list_head = node->tail->list_head;
                insert_AST_head(node, node->head->list_head);
                /* printf("\nsssssssSTATEMENTSSSSSSSSSS\n"); */
                /* AST_NODE *tmp = node->list_head_syn; */
                /* while (tmp != NULL) */
                /* { */
                /*     print_astnode_details(tmp, stdout); */
                /*     tmp = tmp->sibling; */
                /* } */
                /* printf("done\n"); */
            }
            print_astnodes(node);
        }
        else if (node->symbol->non_terminal == Statement) {
            resolve(node->head); // Statement type (io/cond/iter/etc)
            insert_AST_head(node, node->head->list_head);
            print_astnodes(node);
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
        else if (node->symbol->non_terminal == IoStmt){
            if (node->head->symbol->terminal == pRINT){
                AST_NODE *PRINT = create_AST_node("PRINT", NULL);
                insert_AST_head(node, PRINT);
                resolve(node->head->sibling->sibling); // iD
                insert_AST_tail(node, node->head->sibling->sibling->list_head);
            } else {
                AST_NODE *GET_VALUE = create_AST_node("GET_VALUE", NULL);
                insert_AST_head(node, GET_VALUE);
                insert_AST_head(node, GET_VALUE);
                resolve(node->head->sibling->sibling); // iD
                printf("\noutta id %s\n", node->list_head->label);
                insert_AST_tail(node, node->head->sibling->sibling->list_head);
                insert_AST_tail(node, node->head->sibling->sibling->list_head);
                print_astnodes(node);
                printf("\noutta id\n");
            }
        }
    }
}

void run_ast(char *prog_file, char *output_file)
{
    run_parser(prog_file, output_file);
    AST_NODE *AST_ROOT = create_AST_node("MAINPROGRAM", NULL);
    resolve(Parse_Tree_Root->head->head->sibling->sibling);
}

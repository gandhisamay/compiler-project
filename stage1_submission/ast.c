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

// AST_Node *insert_at_head_syn(TreeNode *list_head, AST_Node *node)
// {
//     node->sibling = list_head->list_head_syn;
//     list_head->list_head_syn = node;
//     if (list_head->list_tail_syn == NULL)
//         list_head->list_tail_syn = node;
// }

// AST_Node *insert_at_head_inh(TreeNode *list_head, AST_Node *node)
// {
//     AST_Node* temp = node;
//     while(node->sibling != NULL){
//         node = node->sibling;
//     }
//     node->sibling = list_head->list_head_inh;
//     list_head->list_head_inh = temp;
//     if (list_head->list_tail_inh == NULL)
//         list_head->list_tail_inh = node;
//     free(temp);
// }

// AST_Node *insert_at_end_syn(TreeNode *list_tail, AST_Node *node)
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

// AST_Node *insert_at_end_inh(TreeNode *list_tail, AST_Node *node)
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

// AST_Node *create_AST_Node(char *label)
// {
//     AST_Node *node = (AST_Node *)malloc(sizeof(AST_Node));
//     strcpy(node->label, label);
//     node->head = NULL;
//     node->tail = NULL;
//     node->sibling = NULL;
//     node->data = NULL;
//     node->parent = NULL;
//     return node;
// }

// AST_Node *insert_AST_Node_head(AST_Node *parent, AST_Node *node)
// {
//     AST_Node* temp = node;
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

// AST_Node *insert_AST_Node_tail(AST_Node *parent, AST_Node *node)
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

AST_Node_List *create_AST_Node_list()
{
    AST_Node_List *list = (AST_Node_List *)malloc(sizeof(AST_Node_List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

AST_Node *create_AST_Node(char *label, Symbol *data)
{
    AST_Node *node = (AST_Node *)malloc(sizeof(AST_Node));
    // AST_Node *node = (AST_Node *)malloc(sizeof(AST_Node *));
    strcpy(node->label, label);
    node->data = data;
    node->next = NULL;
    return node;
}

AST_Node *copy_AST_Node(AST_Node *node)
{
    AST_Node *tmp = create_AST_Node(node->label, node->data);
    tmp->next = node->next;
    return tmp;
}

void insert_AST_head(AST_Node_List *list, AST_Node *astnode)
{
    // AST_Node *tmp = astnode;
    // while (tmp->sibling != NULL)
    // {
    //     tmp = tmp->sibling;
    // }
    // if (treenode->list_head == NULL)
    // {
    //     treenode->list_head = astnode;
    //     treenode->list_tail = tmp;
    //     /* while (astnode->sibling != NULL){ */
    //     /*     astnode = astnode->sibling; */
    //     /* } */
    //     /* treenode->list_tail = astnode; */
    // }
    // else
    // {
    //     tmp->sibling = treenode->list_head;
    //     treenode->list->head = astnode;
    //     // printf("\nCHECK %b %b\n", treenode->list_head->sibling == NULL, treenode->list_head->sibling->sibling == NULL);
    // }
    /* AST_Node *temp = copy_AST_Node(astnode); */
    /* while (temp->sibling != NULL){ */
    /*     temp = temp->sibling; */
    /* } */
    /* temp->sibling = treenode->list_head; */
    /* treenode->list_head = astnode; */
    /* if (treenode->list_tail == NULL) */
    /*     treenode->list_tail = temp; */
    /* free(temp); */
    if (list->head == NULL)
    {
        list->head = astnode;
    }
    else
    {
        astnode->next = list->head;
        list->head = astnode;
    }
}

void print_astnodes(TreeNode *node)
{
    AST_Node *tmp = node->list->head;
    while (tmp != NULL)
    {
        print_astnode_details(tmp, stdout);
        tmp = tmp->next;
    }
}

void insert_AST_tail(AST_Node_List *AST_list, AST_Node *astnode)
{
    // if (treenode->list_tail == NULL)
    // {
    //     treenode->list_head = astnode;
    //     treenode->list_tail = astnode;
    // }
    // else
    // {
    //     AST_Node *tmp = treenode->list_tail;
    //     printf("\nIN\n");
    //     AST_Node *temp = copy_AST_Node(astnode);
    //     treenode->list_tail->sibling = temp;
    //     /* printf("CHECK %b %b %b %b\n", temp == NULL, treenode->list_tail->sibling == temp, treenode->list_head->sibling == NULL, treenode->list_tail->sibling == NULL); */
    //     while (tmp->sibling != NULL)
    //     {
    //         tmp = tmp->sibling;
    //     }
    //     treenode->list_tail = tmp;
    // }
    // print_astnodes(treenode);
    // printf("\nOUT\n");
    if (AST_list->head == NULL)
    {
        AST_list->head = astnode;
    }
    else
    {
        AST_Node *curr = AST_list->head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = astnode;
    }

    // AST_list->size++;
}
void append_helper(AST_Node_List *list1, AST_Node *node)
{
    if (node->next == NULL)
    {
        AST_Node *temp = copy_AST_Node(node);
        insert_AST_head(list1, temp);
    }
    else
    {
        append_helper(list1, node->next);
        AST_Node *temp = copy_AST_Node(node);
        insert_AST_head(list1, temp);
    }
}

void append_AST_lists_tail(AST_Node_List *list1, AST_Node_List *list2)
{
    if (list1->head == NULL)
    {
        list1->head = list2->head;
        // list1->tail = list2->tail;
    }
    else
    {
        AST_Node *temp = list1->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = list2->head;
        // free(temp);
    }
}

void append_AST_lists_head(AST_Node_List *list1, AST_Node_List *list2)
{
    // if(list1->head == NULL){
    //     list1->head = list2->head;
    // }
    // else {
    //     AST_Node* temp1 = list1->head;
    //     AST_Node* temp2 = list2->head;

    //     while(temp2->next != NULL){
    //         temp2 = temp2->next;
    //     }
    //     temp2->next = temp1;
    //     list1->head = temp2;

    // }
    AST_Node *curr = list2->head;
    AST_Node *next;
    if (curr != NULL)
    {
        append_helper(list1,list2->head);
    }
    else
    {
        return;
    }
}



void resolve(TreeNode *node)
{

    /* print_symbol_details(node->symbol, stdout); */
    node->list = create_AST_Node_list();
    printf("\n>>>HERE\n");
    if (node->symbol->is_terminal)
    {
        if (node->symbol->terminal == iD)
        {
            AST_Node *ast_id = create_AST_Node("iD", node->symbol);
            // ast_id->data = node->symbol;
            insert_AST_tail(node->list, ast_id);
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
            AST_Node *DRIVER = create_AST_Node("DRIVER", NULL);
            // insert_AST_head(node, DRIVER);
            insert_AST_tail(node->list, DRIVER);
            resolve(node->tail); // ModuleDef
            append_AST_lists_tail(node->list, node->tail->list);
            print_astnodes(node);
        }
        else if (node->symbol->non_terminal == ModuleDef)
        {
            AST_Node *STATEMENTS = create_AST_Node("STATEMENTS", NULL);
            insert_AST_tail(node->list, STATEMENTS);
            resolve(node->head->sibling); // Statements
            append_AST_lists_tail(node->list, node->head->sibling->list);
            print_astnodes(node);
            /* AST_Node *tmp = node->node_syn; */
            /* while (tmp != NULL) */
            /* { */
            /*     print_astnode_details(tmp, stdout); */
            /*     tmp = tmp->sibling; */
            /* } */
        }
        else if (node->symbol->non_terminal == Statements)
        {
            if (node->head->sibling == NULL)
            { // Statements => #
              // node->list_head = NULL;
            }
            else
            {
                resolve(node->tail); // Statements1
                resolve(node->head); // Statement
                append_AST_lists_tail(node->list, node->tail->list);
                append_AST_lists_tail(node->list, node->head->list);
                /* printf("\nsssssssSTATEMENTSSSSSSSSSS\n"); */
                /* AST_Node *tmp = node->list_head_syn; */
                /* while (tmp != NULL) */
                /* { */
                /*     print_astnode_details(tmp, stdout); */
                /*     tmp = tmp->sibling; */
                /* } */
                /* printf("done\n"); */
            }
            print_astnodes(node);
        }
        else if (node->symbol->non_terminal == Statement)
        {
            resolve(node->head); // Statement type (io/cond/iter/etc)
            append_AST_lists_tail(node->list, node->head->list);
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
        else if (node->symbol->non_terminal == IoStmt)
        {
            if (node->head->symbol->terminal == pRINT)
            {
                AST_Node *PRINT = create_AST_Node("PRINT", NULL);
                insert_AST_tail(node->list, PRINT);
                resolve(node->head->sibling->sibling); // iD
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
            }
            else
            {
                AST_Node *GET_VALUE = create_AST_Node("GET_VALUE", NULL);
                insert_AST_tail(node->list, GET_VALUE);
                print_astnodes(node);
                printf("\noutta id\n");

                // insert_AST_tail(node->list, GET_VALUE);
                resolve(node->head->sibling->sibling); // iD
                print_astnodes(node->head->sibling->sibling);
                printf("\noutta id\n");
                // printf("\noutta id %s\n", node->list->head->label);
                append_AST_lists_head(node->list, node->head->sibling->sibling->list);
                // append_AST_lists_tail(node->list, node->head->sibling->sibling->list);

                print_astnodes(node);
                printf("\noutta id\n");
            }
        }
    }
}

void run_ast(char *prog_file, char *output_file)
{
    run_parser(prog_file, output_file);
    AST_Node *AST_ROOT = create_AST_Node("MAINPROGRAM", NULL);
    resolve(Parse_Tree_Root->head->head->sibling->sibling);
}

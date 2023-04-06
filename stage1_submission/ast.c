#include "ast.h"

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
    node->token_set = 0;
    return node;
}
AST_Node *copy_AST_Node(AST_Node *node)
{
    AST_Node *tmp = create_AST_Node(node->label, node->data);
    tmp->next = node->next;
    if (node->token_set == 1)
    {
        tmp->token_set = 1;
        tmp->token = node->token;
    }
    return tmp;
}
void insert_AST_head(AST_Node_List *list, AST_Node *astnode)
{
    if (list->head == NULL)
    {
        list->head = astnode;
    }
    else
    {
        AST_Node *tmp = copy_AST_Node(astnode);
        tmp->next = list->head;
        list->head = tmp;
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
        curr->next = copy_AST_Node(astnode);
    }
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
        AST_Node *temp1 = list1->head;
        AST_Node *temp2 = list2->head;
        while (temp1->next != NULL)
        {
            temp1 = temp1->next;
        }

        while (temp2 != NULL)
        {
            temp1->next = copy_AST_Node(temp2);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        // free(temp);
    }
}
void append_AST_lists_head(AST_Node_List *list1, AST_Node_List *list2)
{
    AST_Node *curr = list2->head;
    AST_Node *next;
    if (curr != NULL)
    {
        append_helper(list1, list2->head);
    }
    else
    {
        return;
    }
}

void resolve(TreeNode *node)
{
    node->list = create_AST_Node_list();
    printf("\n>>>HERE\n");
    if (node->symbol->is_terminal)
    {
        if (node->symbol->terminal == iD)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        if (node->symbol->terminal == iNTEGER)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        if (node->symbol->terminal == rEAL)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        if (node->symbol->terminal == bOOLEAN)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
    }
    else
    {
        if (node->symbol->non_terminal == Program)
        {
            resolve(node->head);                   // ModuleDeclarations
            resolve(node->head->sibling->sibling); // DriverModule
            AST_Node *module_declarations = create_AST_Node("MODULEDECLARATIONS", NULL);
            AST_Node *main_program = create_AST_Node("MAINPROGRAM", NULL);
            insert_AST_head(node->list, main_program);
            insert_AST_tail(node->list, module_declarations);
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
        }
        else if (node->symbol->non_terminal == ModuleDeclarations)
        {
            if (node->head->sibling == NULL)
            {
                // ModuleDeclarations => #
            }
            else
            {
                resolve(node->tail); // ModuleDeclarations1 child
                resolve(node->head); // ModuleDeclaration
                /* node->list = node->tail->list; */
                append_AST_lists_head(node->list, node->tail->list);
                append_AST_lists_head(node->list, node->head->list);
            }
        }
        else if (node->symbol->non_terminal == ModuleDeclaration)
        {
            resolve(node->head->sibling->sibling); // iD
            insert_AST_head(node->list, node->head->sibling->sibling->list->head);
        }
        else if (node->symbol->non_terminal == DriverModule)
        {
            AST_Node *DRIVER = create_AST_Node("DRIVER", NULL);
            insert_AST_tail(node->list, DRIVER);
            resolve(node->tail); // ModuleDef
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == ModuleDef)
        {
            AST_Node *STATEMENTS = create_AST_Node("STATEMENTS", NULL);
            insert_AST_tail(node->list, STATEMENTS);
            resolve(node->head->sibling); // Statements
            append_AST_lists_tail(node->list, node->head->sibling->list);
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
            }
        }
        else if (node->symbol->non_terminal == Statement)
        {
            resolve(node->head); // Statement type (io/cond/iter/etc)
            append_AST_lists_tail(node->list, node->head->list);
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
                resolve(node->head->sibling->sibling); // iD
                insert_AST_tail(node->list, node->head->sibling->sibling->list->head);
            }
        }
        else if(node->symbol->non_terminal == DeclareStmt){
            AST_Node* DECLARE = create_AST_Node("DECLARE", NULL);
            insert_AST_tail(node->list,DECLARE);
            resolve(node->head->sibling);
            resolve(node->head->sibling->sibling->sibling);
            append_AST_lists_tail(node->list,node->head->sibling->list);
            append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->list);
        }
        else if(node->symbol->non_terminal == IdList){
            resolve(node->head);
            resolve(node->tail);
            append_AST_lists_tail(node->list,node->head->list);
            append_AST_lists_head (node->list,node->tail->list);
        }
        else if (node->symbol->non_terminal == N3){
            if(node->head->sibling == NULL){

            }
            else {
                resolve(node->head->sibling);
                resolve(node->tail);
                append_AST_lists_tail(node->list,node->head->sibling->list);
                append_AST_lists_tail(node->list,node->tail->list);
            }
        }
        else if( node->symbol->non_terminal == DataType){
            if(node->head->sibling==NULL){
                resolve(node->head);
                insert_AST_tail(node->list,node->head->list->head);                
            }
            else {
                AST_Node* ARRAY = create_AST_Node("ARRAY",NULL);
                insert_AST_tail(node->list, ARRAY);
                resolve(node->head->sibling->sibling);
                resolve(node->tail);
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
            }
        }
        else if (node->symbol->non_terminal == IterativeStmt)
        {   
            if (node->head->symbol->terminal == fOR){
                AST_Node* FORLOOP = create_AST_Node("FORLOOP",NULL);
                insert_AST_tail(node->list,FORLOOP);
                resolve(node->head->sibling->sibling);
                resolve(node->head->sibling->sibling->sibling->sibling);
                resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling);
                append_AST_lists_tail(node->list,node->head->sibling->sibling->list);
                append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->sibling->list);
                append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list);
            }
            else {
                AST_Node* WHILELOOP  = create_AST_Node("WHILELOOP",NULL);
                insert_AST_tail(node->list,WHILELOOP);
                resolve(node->head->sibling->sibling);
                resolve(node->head->sibling->sibling->sibling->sibling->sibling);
                append_AST_lists_tail(node->list,node->head->sibling->sibling);
                append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->sibling->sibling->list);
            }
        }
        else if(node->symbol->non_terminal == Range_for_loop){
            resolve(node->head);
            resolve(node->tail);
            append_AST_lists_tail(node->list,node->head->list);
            append_AST_lists_tail(node->list,node->tail->list);
        }
        else if(node->symbol->non_terminal == Index_for_loop){
            resolve(node->head);
            resolve(node->tail);
            append_AST_lists_tail(node->list,node->head->list->head);
            append_AST_lists_tail(node->list,node->tail->list->head);
        }
        else
    }
}

void run_ast(char *prog_file, char *output_file)
{
    run_parser(prog_file, output_file);
    resolve(Parse_Tree_Root->head);
    print_astnodes(Parse_Tree_Root->head);
    printf("\n\n");
}

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
            AST_Node *main_program = create_AST_Node("MAINPROGRAM", NULL);
            AST_Node *module_declarations = create_AST_Node("MODULEDECLARATIONS", NULL);
            AST_Node *module_definitions = create_AST_Node("MODULEDEFINITIONS", NULL);
            AST_Node *module_definitions1 = create_AST_Node("MODULEDEFINITIONS", NULL);
            insert_AST_head(node->list, main_program);
            insert_AST_tail(node->list, module_declarations);
            append_AST_lists_tail(node->list, node->head->list); // append ModuleDeclarations
            insert_AST_tail(node->list, module_definitions);
            resolve(node->head->sibling); // OtherModules
            append_AST_lists_tail(node->list, node->head->sibling->list); // append OtherModules
            append_AST_lists_tail(node->list, node->head->sibling->sibling->list); // append DriverModule
            insert_AST_tail(node->list, module_definitions1);
            resolve(node->tail); // OtherModules1
            append_AST_lists_tail(node->list, node->tail->list); // append OtherModules1
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
                append_AST_lists_head(node->list, node->tail->list);
                append_AST_lists_head(node->list, node->head->list);
            }
        }
        else if (node->symbol->non_terminal == ModuleDeclaration)
        {
            resolve(node->head->sibling->sibling); // iD
            insert_AST_head(node->list, node->head->sibling->sibling->list->head);
        }
        else if (node->symbol->non_terminal == OtherModules){
            if (node->head->sibling == NULL){
                // OtherModules => #
            } else {
                resolve(node->tail); // OtherModules1 child
                resolve(node->head); // Module
                append_AST_lists_tail(node->list, node->tail->list);
                append_AST_lists_head(node->list, node->head->list);
            }
        }
        else if (node->symbol->non_terminal == Module){
            AST_Node *module = create_AST_Node("MODULE", NULL);
            AST_Node *input_plist = create_AST_Node("INPUT_PARAMETERS_LIST", NULL);
            insert_AST_head(node->list, module);
            // resolve and add ID
            resolve(node->head->sibling->sibling); // iD
            insert_AST_tail(node->list, node->head->sibling->sibling->list->head); // insert iD
            // resolve and add Input_plist
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling); // Input_plist
            insert_AST_tail(node->list, input_plist);
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list); // insert plist
            // resolve and add Return_plist
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling); // RET
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list); // insert RET
            // resolve and add ModuleDef
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling); // ModuleDef
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list); // insert ModuleDef
        }
        else if (node->symbol->non_terminal == Ret){
            AST_Node *return_plist = create_AST_Node("RETURN_PARAMETERS_LIST", NULL);
            insert_AST_tail(node->list, return_plist);
            if (node->head->sibling == NULL){
                // Ret => #
            } else {
                resolve(node->head->sibling->sibling); // Output_plist
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list); // insert Output_plist
            }
        }
        else if (node->symbol->non_terminal == Input_plist){
            resolve(node->head); // iD
            resolve(node->head->sibling->sibling); // Type
            resolve(node->head->sibling->sibling->sibling);  // N1
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->list); // appending to N1
            insert_AST_head(node->list, node->head->sibling->sibling->list->head); // insert type at head to N1
            insert_AST_head(node->list, node->head->list->head); // insert iD at head to N1
        }
        else if (node->symbol->non_terminal == Output_plist){
            resolve(node->head); // iD
            resolve(node->head->sibling->sibling); // Type
            resolve(node->head->sibling->sibling->sibling);  // N2
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->list); // appending to N2
            insert_AST_head(node->list, node->head->sibling->sibling->list->head); // insert type at head to N2
            insert_AST_head(node->list, node->head->list->head); // insert iD at head to N2
        }
        else if (node->symbol->non_terminal == DataType){
            if (node->head->sibling == NULL){
                AST_Node *type = create_AST_Node("", node->head->symbol);            
                type->token_set = 1;
                type->token = node->head->token;
                insert_AST_head(node->list, type);
            } else {
                AST_Node *array = create_AST_Node("ARRAY", node->head->symbol);            
                insert_AST_head(node->list, array);
                resolve(node->tail); // Type
                insert_AST_tail(node->list, node->tail->list->head); // add Type
                resolve(node->head->sibling->sibling); // Range_arrays
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list); // append Range_arrays
            }
        }
        else if (node->symbol->non_terminal == Range_arrays){
            resolve(node->head); // Index_arr1
            resolve(node->tail); // Index_arr2
            AST_Node *range = create_AST_Node("RANGE_ARRAY", node->head->symbol);            
            insert_AST_head(node->list, range);
            append_AST_lists_tail(node->list, node->head->list); // append Index_arr1
            append_AST_lists_tail(node->list, node->tail->list); // append Index_arr2
        }
        else if (node->symbol->non_terminal == Index_arr){
            AST_Node *range_index = create_AST_Node("RANGE_ARRAY_INDEX", node->head->symbol);            
            insert_AST_head(node->list, range_index);
            if (node->head->sibling == NULL){
                AST_Node *new_index = create_AST_Node("", node->head->head->symbol);            
                new_index->token_set = 1;
                new_index->token = node->head->head->token;
                insert_AST_tail(node->list, new_index); // insert new_index
            } else {
                AST_Node *sign = create_AST_Node("", node->head->head->symbol);            
                sign->token_set = 1;
                sign->token = node->head->head->token;
                insert_AST_tail(node->list, sign); // insert sign
                AST_Node *new_index = create_AST_Node("", node->head->sibling->head->symbol);            
                new_index->token_set = 1;
                new_index->token = node->head->sibling->head->token;
                insert_AST_tail(node->list, new_index); // insert new_index
            }
        }
        else if (node->symbol->non_terminal == Type){
            AST_Node *type = create_AST_Node("", node->head->symbol);            
            type->token_set = 1;
            type->token = node->head->token;
            insert_AST_head(node->list, type);
        }
        else if (node->symbol->non_terminal == N2){
            if (node->head->sibling == NULL){
                // N2 => #
            } else {
                resolve(node->tail); // N21 child
                resolve(node->head->sibling); // iD
                resolve(node->head->sibling->sibling->sibling); // Type
                append_AST_lists_tail(node->list, node->tail->list); // N2.syn_list = N21.syn_list
                insert_AST_head(node->list, node->head->sibling->sibling->sibling->list->head); // add type to list head
                insert_AST_head(node->list, node->head->sibling->list->head); // add iD to list head
            }
        }
        else if (node->symbol->non_terminal == N1){
            if (node->head->sibling == NULL){
                // N1 => #
            } else {
                resolve(node->tail); // N11 child
                resolve(node->head->sibling); // iD
                resolve(node->head->sibling->sibling->sibling); // Type
                append_AST_lists_tail(node->list, node->tail->list); // N1.syn_list = N11.syn_list
                insert_AST_head(node->list, node->head->sibling->sibling->sibling->list->head); // add type to list head
                insert_AST_head(node->list, node->head->sibling->list->head); // add iD to list head
            }
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

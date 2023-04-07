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
        else if (node->symbol->terminal == iNTEGER)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == rEAL)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == bOOLEAN)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == nUM)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == rNUM)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == aND)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == oR)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == mUL)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == dIV)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == pLUS)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == mINUS)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == tRUE)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == fALSE)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }else if (node->symbol->terminal == lT)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == lE)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == gE)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == gT)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == eQ)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
        else if (node->symbol->terminal == nE)
        {
            AST_Node *ast_id = create_AST_Node("", node->symbol);
            ast_id->token = node->token;
            ast_id->token_set = 1;
            insert_AST_tail(node->list, ast_id);
        }
    }
    else
    {
        if (node->head == NULL){
            return;
        }
        else if (node->symbol->non_terminal == Program)
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
            resolve(node->head->sibling);                                          // OtherModules
            append_AST_lists_tail(node->list, node->head->sibling->list);          // append OtherModules
            append_AST_lists_tail(node->list, node->head->sibling->sibling->list); // append DriverModule
            insert_AST_tail(node->list, module_definitions1);
            resolve(node->tail);                                 // OtherModules1
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
        else if (node->symbol->non_terminal == OtherModules)
        {
            if (node->head->sibling == NULL)
            {
                // OtherModules => #
            }
            else
            {
                resolve(node->tail); // OtherModules1 child
                resolve(node->head); // Module
                append_AST_lists_tail(node->list, node->tail->list);
                append_AST_lists_head(node->list, node->head->list);
            }
        }
        else if (node->symbol->non_terminal == Module)
        {
            AST_Node *module = create_AST_Node("MODULE", NULL);
            AST_Node *input_plist = create_AST_Node("INPUT_PARAMETERS_LIST", NULL);
            insert_AST_head(node->list, module);
            // resolve and add ID
            resolve(node->head->sibling->sibling);                                 // iD
            insert_AST_tail(node->list, node->head->sibling->sibling->list->head); // insert iD
            // resolve and add Input_plist
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling); // Input_plist
            insert_AST_tail(node->list, input_plist);
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list); // insert plist
            // resolve and add Return_plist
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling);                                 // RET
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list); // insert RET
            // resolve and add ModuleDef
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling);                                 // ModuleDef
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list); // insert ModuleDef
        }
        else if (node->symbol->non_terminal == Ret)
        {
            AST_Node *return_plist = create_AST_Node("RETURN_PARAMETERS_LIST", NULL);
            insert_AST_tail(node->list, return_plist);
            if (node->head->sibling == NULL)
            {
                // Ret => #
            }
            else
            {
                resolve(node->head->sibling->sibling);                                 // Output_plist
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list); // insert Output_plist
            }
        }
        else if (node->symbol->non_terminal == Input_plist)
        {
            resolve(node->head);                                                            // iD
            resolve(node->head->sibling->sibling);                                          // Type
            resolve(node->head->sibling->sibling->sibling);                                 // N1
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->list); // appending to N1
            append_AST_lists_head(node->list, node->head->sibling->sibling->list);          // append Type at head to N1
            insert_AST_head(node->list, node->head->list->head);                            // insert iD at head to N1
        }
        else if (node->symbol->non_terminal == Output_plist)
        {
            resolve(node->head);                                                            // iD
            resolve(node->head->sibling->sibling);                                          // Type
            resolve(node->head->sibling->sibling->sibling);                                 // N2
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->list); // appending to N2
            insert_AST_head(node->list, node->head->sibling->sibling->list->head);          // insert type at head to N2
            insert_AST_head(node->list, node->head->list->head);                            // insert iD at head to N2
        }
        else if (node->symbol->non_terminal == DataType)
        {
            if (node->head->sibling == NULL)
            {
                AST_Node *type = create_AST_Node("", node->head->symbol);
                type->token_set = 1;
                type->token = node->head->token;
                insert_AST_head(node->list, type);
            }
            else
            {
                AST_Node *array = create_AST_Node("ARRAY", node->head->symbol);
                insert_AST_head(node->list, array);
                resolve(node->tail);                                                   // Type
                insert_AST_tail(node->list, node->tail->list->head);                   // add Type
                resolve(node->head->sibling->sibling);                                 // Range_arrays
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list); // append Range_arrays
            }
        }
        else if (node->symbol->non_terminal == Range_arrays)
        {
            resolve(node->head); // Index_arr1
            resolve(node->tail); // Index_arr2
            AST_Node *range = create_AST_Node("RANGE_ARRAY", node->head->symbol);
            insert_AST_head(node->list, range);
            append_AST_lists_tail(node->list, node->head->list); // append Index_arr1
            append_AST_lists_tail(node->list, node->tail->list); // append Index_arr2
        }
        else if (node->symbol->non_terminal == Index_arr)
        {
            AST_Node *range_index = create_AST_Node("RANGE_ARRAY_INDEX", node->head->symbol);
            insert_AST_head(node->list, range_index);
            if (node->head->sibling == NULL)
            {
                AST_Node *new_index = create_AST_Node("", node->head->head->symbol);
                new_index->token_set = 1;
                new_index->token = node->head->head->token;
                insert_AST_tail(node->list, new_index); // insert new_index
            }
            else
            {
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
        else if (node->symbol->non_terminal == Type)
        {
            AST_Node *type = create_AST_Node("", node->head->symbol);
            type->token_set = 1;
            type->token = node->head->token;
            insert_AST_head(node->list, type);
        }
        else if (node->symbol->non_terminal == N2)
        {
            if (node->head->sibling == NULL)
            {
                // N2 => #
            }
            else
            {
                resolve(node->tail);                                                            // N21 child
                resolve(node->head->sibling);                                                   // iD
                resolve(node->head->sibling->sibling->sibling);                                 // Type
                append_AST_lists_tail(node->list, node->tail->list);                            // N2.syn_list = N21.syn_list
                insert_AST_head(node->list, node->head->sibling->sibling->sibling->list->head); // add type to list head
                insert_AST_head(node->list, node->head->sibling->list->head);                   // add iD to list head
            }
        }
        else if (node->symbol->non_terminal == N1)
        {
            if (node->head->sibling == NULL)
            {
                // N1 => #
            }
            else
            {
                resolve(node->tail);                                                            // N11 child
                resolve(node->head->sibling);                                                   // iD
                resolve(node->head->sibling->sibling->sibling);                                 // Type
                append_AST_lists_tail(node->list, node->tail->list);                            // N1.syn_list = N11.syn_list
                insert_AST_head(node->list, node->head->sibling->sibling->sibling->list->head); // add type to list head
                insert_AST_head(node->list, node->head->sibling->list->head);                   // add iD to list head
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
                append_AST_lists_head(node->list, node->head->list);
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
        else if (node->symbol->non_terminal == ConditionalStmt)
        {
            resolve(node->head->sibling->sibling); // iD
            AST_Node *switch_node = create_AST_Node("SWITCH", NULL);
            AST_Node *cases = create_AST_Node("CASES", NULL);
            insert_AST_tail(node->list, switch_node);                                                                  // insert SWITCH
            insert_AST_tail(node->list, node->head->sibling->sibling->list->head);                                     // insert iD
            insert_AST_tail(node->list, cases);                                                                        // insert CASES
            resolve(node->head->sibling->sibling->sibling->sibling->sibling);                                          // CaseStmts
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling);                                 // Default
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->list);          // appending CaseStmts
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->list); // appending Default
        }
        else if (node->symbol->non_terminal == CaseStmts)
        {
            AST_Node *stmts = create_AST_Node("STATEMENTS", NULL);
            AST_Node *case_node = create_AST_Node("CASE", NULL);
            resolve(node->head->sibling);                                                   // Value
            resolve(node->head->sibling->sibling->sibling);                                 // Statements
            resolve(node->tail);                                                            // N9
            append_AST_lists_tail(node->list, node->tail->list);                            // append N9 list
            append_AST_lists_head(node->list, node->head->sibling->sibling->sibling->list); // append Statements list to head
            insert_AST_head(node->list, stmts);                                             // insert STATEMENTS to head
            insert_AST_head(node->list, node->head->sibling->list->head);                   // insert Value to head
            insert_AST_head(node->list, case_node);                                         // insert CASE to head
        }
        else if (node->symbol->non_terminal == Value)
        {
            AST_Node *val = create_AST_Node("", node->head->symbol);
            val->token_set = 1;
            val->token = node->head->token;
            insert_AST_head(node->list, val);
        }
        else if (node->symbol->non_terminal == N9)
        {
            if (node->head->sibling == NULL)
            {
                // N9 => #
            }
            else
            {
                AST_Node *stmts = create_AST_Node("STATEMENTS", NULL);
                AST_Node *case_node = create_AST_Node("CASE", NULL);
                resolve(node->head->sibling);                                                   // Value
                resolve(node->head->sibling->sibling->sibling);                                 // Statements
                resolve(node->tail);                                                            // N91 child
                append_AST_lists_tail(node->list, node->tail->list);                            // append N91 child
                append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->list); // append Statements to head
                insert_AST_head(node->list, stmts);                                             // insert STATEMENTS to head
                insert_AST_head(node->list, node->head->sibling->list->head);                   // insert Value to head
                insert_AST_head(node->list, case_node);                                         // insert CASE to head
            }
        }
        else if (node->symbol->non_terminal == Default)
        {
            if (node->head->sibling == NULL){
                // Default => #
            } else {
                AST_Node *default_node = create_AST_Node("DEFAULTCASE", NULL);
                AST_Node *stmts = create_AST_Node("STATEMENTS", NULL);
                insert_AST_tail(node->list, default_node);                             // insert DEFAULTCASE
                insert_AST_tail(node->list, stmts);                                    // insert STATEMENTS
                resolve(node->head->sibling->sibling);                                 // Statements
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list); // append Statements list
            }
        }
        else if (node->symbol->non_terminal == IoStmt)
        {
            if (node->head->symbol->terminal == pRINT)
            {
                AST_Node *PRINT = create_AST_Node("PRINT", NULL);
                insert_AST_tail(node->list, PRINT);
                resolve(node->head->sibling->sibling); // Var_print
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
        else if (node->symbol->non_terminal == Var_print)
        {
            if (node->head->sibling != NULL)
            {
                if (node->head->sibling->head->sibling == NULL)
                {                                                        // only iD
                    resolve(node->head);                                 // iD
                    append_AST_lists_tail(node->list, node->head->list); // append iD
                }
                else
                { // iD with ARRAY_ACCESS
                    AST_Node *array_access = create_AST_Node("ARRAY_ACCESS", NULL);
                    resolve(node->head);                                          // iD
                    resolve(node->head->sibling);                                 // P1
                    insert_AST_head(node->list, array_access);                    // insert ARRAY_ACCESS
                    append_AST_lists_tail(node->list, node->head->list);          // append iD
                    append_AST_lists_tail(node->list, node->head->sibling->list); // append P1
                }
            }
            else
            {
                if (node->head->head == NULL)
                {
                    resolve(node->head);                                 // nUM/rNUM
                    insert_AST_head(node->list, node->head->list->head); // insert nUM/rNUM
                }
                else
                {
                    resolve(node->head);                                 // BoolConstt
                    append_AST_lists_head(node->list, node->head->list); // append BoolConstt
                }
            }
        }
        else if (node->symbol->non_terminal == P1)
        {
            if (node->head->sibling == NULL)
            {
                // P1 => #
            }
            else
            {
                resolve(node->head->sibling);                                 // Index_arr
                append_AST_lists_head(node->list, node->head->sibling->list); // append Index_arr
            }
        }
        else if (node->symbol->non_terminal == BoolConstt)
        {
            resolve(node->head);                                 // tRUE/fALSE
            insert_AST_head(node->list, node->head->list->head); // insert tRUE/fALSE
        }
        else if (node->symbol->non_terminal == DeclareStmt)
        {
            AST_Node *DECLARE = create_AST_Node("DECLARE", NULL);
            insert_AST_tail(node->list, DECLARE);
            resolve(node->head->sibling);                   // IdList
            resolve(node->head->sibling->sibling->sibling); // DataType
            append_AST_lists_tail(node->list, node->head->sibling->list);
            append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->list);
        }
        else if (node->symbol->non_terminal == IdList)
        {
            resolve(node->head); // iD
            resolve(node->tail); // N3
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_head(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == N3)
        {
            if (node->head->sibling == NULL)
            {
            }
            else
            {
                resolve(node->head->sibling); // iD
                resolve(node->tail);          // N3
                append_AST_lists_tail(node->list, node->head->sibling->list);
                append_AST_lists_tail(node->list, node->tail->list);
            }
        }
        // else if( node->symbol->non_terminal == DataType){
        //     if(node->head->sibling==NULL){
        //         resolve(node->head);
        //         insert_AST_tail(node->list,node->head->list->head);
        //     }
        //     else {
        //         AST_Node* ARRAY = create_AST_Node("ARRAY",NULL);
        //         insert_AST_tail(node->list, ARRAY);
        //         resolve(node->head->sibling->sibling);
        //         resolve(node->tail);
        //         append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
        //     }
        // }
        else if (node->symbol->non_terminal == IterativeStmt)
        {
            if (node->head->symbol->terminal == fOR)
            {
                AST_Node *FORLOOP = create_AST_Node("FORLOOP", NULL);
                AST_Node *STATEMENTS = create_AST_Node("STATEMENTS", NULL);
                insert_AST_tail(node->list, FORLOOP);
                resolve(node->head->sibling->sibling);                                              // iD
                resolve(node->head->sibling->sibling->sibling->sibling);                            // Range_for_loop
                resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling); // Statements
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
                append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->list);
                insert_AST_tail(node->list, STATEMENTS);
                append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->list);
            }
            else
            {
                AST_Node *WHILELOOP = create_AST_Node("WHILELOOP", NULL);
                AST_Node *STATEMENTS = create_AST_Node("STATEMENTS", NULL);
                insert_AST_tail(node->list, WHILELOOP);
                resolve(node->head->sibling->sibling);                            // ArithmeticOrBooleanExpr
                resolve(node->head->sibling->sibling->sibling->sibling->sibling); // Statements
                append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
                insert_AST_tail(node->list, STATEMENTS);
                append_AST_lists_tail(node->list, node->head->sibling->sibling->sibling->sibling->sibling->list);
            }
        }
        else if (node->symbol->non_terminal == Range_for_loop)
        {
            resolve(node->head); // Index_for_loop
            resolve(node->tail); // Index_for_loop
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == Index_for_loop)
        {
            AST_Node *INDEX_FOR_LOOP = create_AST_Node("INDEX_FOR_LOOP", NULL);

            insert_AST_tail(node->list, INDEX_FOR_LOOP);
            resolve(node->head); // Sign_for_loop
            resolve(node->tail); // New_index_for_loop

            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == Sign_for_loop)
        {
            if (node->head == NULL)
            {
            }
            else
            {
                resolve(node->head); // plus/minus
                insert_AST_tail(node->list, node->head->list->head);
            }
        }
        else if (node->symbol->non_terminal == New_index_for_loop)
        {
            resolve(node->head); // num
            insert_AST_tail(node->list, node->head->list->head);
        }
        else if (node->symbol->non_terminal == SimpleStmt)
        {
            resolve(node->head); // AssignStmt/ModuleReuseStmt
            append_AST_lists_tail(node->list, node->head->list);
        }
        else if (node->symbol->non_terminal == AssignmentStmt)
        {
            AST_Node *ASSIGNSTMT = create_AST_Node("ASSIGNSTMT", NULL);
            insert_AST_tail(node->list, ASSIGNSTMT);
            resolve(node->head); // id
            resolve(node->tail); // WhichStmt
            insert_AST_tail(node->list, node->head->list->head);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == WhichStmt)
        {
            resolve(node->head); // LvalueID/LvalueARR
            append_AST_lists_tail(node->list, node->head->list);
        }
        else if (node->symbol->non_terminal == LvalueIDStmt)
        {
            AST_Node *LVALUEID = create_AST_Node("LVALUEID", NULL);
            insert_AST_tail(node->list, LVALUEID);
            resolve(node->head->sibling); // Expression
            append_AST_lists_tail(node->list, node->head->sibling->list);
        }
        else if (node->symbol->non_terminal == Expression)
        {
            resolve(node->head); // ArithmeticOrBool/U
            append_AST_lists_tail(node->list, node->head->list);
        }
        else if (node->symbol->non_terminal == ArithmeticOrBooleanExpr)
        {
            AST_Node *ARITHORBOOLEXP = create_AST_Node("ARITHORBOOLEXP", NULL);
            insert_AST_tail(node->list, ARITHORBOOLEXP);
            resolve(node->head); // AnyTerm
            resolve(node->tail); // N7
            AST_Node* LOGIC;
            if(node->tail->head->sibling == NULL){

            }
            else {
                if(node->tail->head->head->symbol->terminal == aND){
                    LOGIC = create_AST_Node("AND",NULL);
                }
                else {
                    LOGIC = create_AST_Node("OR",NULL);
                }
                insert_AST_tail(node->list,LOGIC);
            }
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == AnyTerm)
        {
            resolve(node->head); // ArithmeticExpr
            resolve(node->tail); // N8
            AST_Node* REL;
            if(node->tail->head->sibling == NULL){

            }
            else {
                if(node->tail->head->head->symbol->terminal == lT){
                    REL = create_AST_Node("LT",NULL);
                }
                else if(node->tail->head->head->symbol->terminal == lE){
                    REL = create_AST_Node("LE",NULL);
                }
                else if(node->tail->head->head->symbol->terminal == gT){
                    REL = create_AST_Node("GT",NULL);
                }
                else if(node->tail->head->head->symbol->terminal == gE){
                    REL = create_AST_Node("GE",NULL);
                }
                else if(node->tail->head->head->symbol->terminal == eQ){
                    REL = create_AST_Node("EQ",NULL);
                }
                else if(node->tail->head->head->symbol->terminal == nE){
                    REL = create_AST_Node("NE",NULL);
                }
                insert_AST_tail(node->list,REL);
            }
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == ArithmeticExpr)
        {   
            resolve(node->head); // Term
            resolve(node->tail); // N4
            AST_Node* OP1;
            if(node->tail->head->sibling == NULL){

            }
            else {
                if(node->tail->head->head->symbol->terminal == pLUS){
                    OP1 = create_AST_Node("ADD",NULL);
                }
                else {
                    OP1 = create_AST_Node("SUBTRACT",NULL);
                }
                insert_AST_tail(node->list,OP1);
            }
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == Term)
        {
            resolve(node->head); // Factor
            resolve(node->tail); // N5
            AST_Node* OP2;
                if(node->tail->head->sibling == NULL){

                }
                else {
                    if(node->tail->head->head->symbol->terminal == mUL){
                        OP2 = create_AST_Node("MUL",NULL);
                    }
                    else {
                        OP2 = create_AST_Node("DIV",NULL);
                    }
                    insert_AST_tail(node->list,OP2);
                }
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == Factor)
        {
            if (node->head->sibling == NULL)
            {
                resolve(node->head); // num/rnum/boolconst
                insert_AST_tail(node->list, node->head->list->head);
            }
            else if (node->head->sibling->sibling == NULL)
            {
                resolve(node->head); // iD
                resolve(node->tail); // N11
                append_AST_lists_tail(node->list, node->head->list);
                append_AST_lists_tail(node->list, node->tail->list);
            }
            else
            {
                resolve(node->head->sibling); // ArithmeticOrBool
                append_AST_lists_tail(node->list, node->head->sibling->list);
            }
        }
        else if (node->symbol->non_terminal == N11)
        {
            if (node->head->sibling == NULL)
            {
            }
            else
            {
                resolve(node->head->sibling); // Element_index_with_expression
                append_AST_lists_tail(node->list, node->head->sibling->list);
            }
        }
        else if (node->symbol->non_terminal == Element_index_with_expressions)
        {
            if (node->head->sibling == NULL)
            {   
                // AST_Node* ARR_EXP = create_AST_Node("ARR_EXP",NULL);
                resolve(node->head); // ArrExpr
                // insert_AST_tail(node->list,ARR_EXP);
                append_AST_lists_tail(node->list, node->head->list);
            }
            else
            {   
                AST_Node* ARR_INDEX = create_AST_Node("ARR_INDEX",NULL);

                resolve(node->head); // Sign
                resolve(node->tail); // N10
                insert_AST_tail(node->list,ARR_INDEX);
                append_AST_lists_tail(node->list, node->head->list);
                append_AST_lists_tail(node->list, node->tail->list);
            }
        }
        else if (node->symbol->non_terminal == Sign)
        {
            resolve(node->head); // plus/minus
            insert_AST_tail(node->list, node->head->list->head);
        }
        else if (node->symbol->non_terminal == N10)
        {
            if (node->head->sibling == NULL)
            {
                resolve(node->head); // New_index
                insert_AST_tail(node->list, node->head->list->head);
            }
            else
            {
                resolve(node->head); // sign
                resolve(node->tail); // New_index
                insert_AST_tail(node->list, node->head->list->head);
                insert_AST_tail(node->list, node->tail->list->head);
            }
        }
        else if (node->symbol->non_terminal == New_index)
        {
            resolve(node->head); // num/ind
            insert_AST_tail(node->list, node->head->list->head);
        }
        else if (node->symbol->non_terminal == ArrExpr)
        {
            AST_Node *ARREXPR = create_AST_Node("ARREXPR", NULL);
            insert_AST_tail(node->list, ARREXPR);
            resolve(node->head); // ArrTerm
            resolve(node->tail); // Arr_N4
            AST_Node* OP1;
            if(node->tail->head->sibling == NULL){

            }
            else {
                if(node->tail->head->head->symbol->terminal == pLUS){
                    OP1 = create_AST_Node("ADD",NULL);
                }
                else {
                    OP1 = create_AST_Node("SUBTRACT",NULL);
                }
                insert_AST_tail(node->list,OP1);
            }
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == ArrTerm)
        {
            resolve(node->head); // ArrFactor
            resolve(node->tail); // Arr_N5
            AST_Node* OP2;
            if(node->tail->head->sibling == NULL){

            }
            else {
                if(node->tail->head->head->symbol->terminal == mUL){
                    OP2 = create_AST_Node("MUL",NULL);
                }
                else {
                    OP2 = create_AST_Node("DIV",NULL);
                }
                insert_AST_tail(node->list,OP2);
            }
            append_AST_lists_tail(node->list, node->head->list);
            append_AST_lists_tail(node->list, node->tail->list);
        }
        else if (node->symbol->non_terminal == ArrFactor)
        {
            if (node->head->sibling == NULL)
            {
                resolve(node->head); // id/num/boolconst
                insert_AST_tail(node->list, node->head->list->head);
            }
            else
            {
                resolve(node->head->sibling); // ArrExpr
                insert_AST_tail(node->list, node->head->sibling->list->head);
            }
        }
        else if (node->symbol->non_terminal == Arr_N4)
        {
            if (node->head->sibling == NULL)
            {
            }
            else
            {
                resolve(node->head);          // Op1
                resolve(node->head->sibling); // ArrTerm
                resolve(node->tail);          // Arr_N4

                append_AST_lists_tail(node->list, node->head->list);
                AST_Node* OP1;
                if(node->tail->head->sibling == NULL){

                }
                else {
                    if(node->tail->head->head->symbol->terminal == pLUS){
                        OP1 = create_AST_Node("ADD",NULL);
                    }
                    else {
                        OP1 = create_AST_Node("SUBTRACT",NULL);
                    }
                    insert_AST_tail(node->list,OP1);
                }
                append_AST_lists_tail(node->list, node->head->sibling->list);
                append_AST_lists_tail(node->list, node->tail->list);
            }
        }
        else if (node->symbol->non_terminal == Arr_N5)
        {
            if (node->head->sibling == NULL)
            {
            }
            else
            {
                resolve(node->head);          // Op2
                resolve(node->head->sibling); // ArrFactor
                resolve(node->tail);          // Arr_N5
                append_AST_lists_tail(node->list, node->head->list);
                AST_Node* OP2;
                if(node->tail->head->sibling == NULL){

                }
                else {
                    if(node->tail->head->head->symbol->terminal == mUL){
                        OP2 = create_AST_Node("MUL",NULL);
                    }
                    else {
                        OP2 = create_AST_Node("DIV",NULL);
                    }
                    insert_AST_tail(node->list,OP2);
                }
                append_AST_lists_tail(node->list, node->head->sibling->list);
                append_AST_lists_tail(node->list, node->tail->list);
            }
        }
        else if (node->symbol->non_terminal == Op1)
        {
            resolve(node->head);
            insert_AST_tail(node->list, node->head->list->head);
        }
        else if (node->symbol->non_terminal == Op2)
        {
            resolve(node->head);
            insert_AST_tail(node->list, node->head->list->head);
        }
        else if (node->symbol->non_terminal == N5)
        {
            if (node->head->sibling == NULL)
            {
            }
            else
            {
                resolve(node->head);          // Op2
                resolve(node->head->sibling); // Factor
                resolve(node->tail);          // N5
                insert_AST_tail(node->list, node->head->list->head);
                append_AST_lists_tail(node->list, node->head->sibling->list);
                append_AST_lists_tail(node->list, node->tail->list);
            }
        }
        else if (node->symbol->non_terminal == N4)
        {
            if (node->head->sibling == NULL)
            {
            }
            else
            {
                resolve(node->head);          // Op1
                resolve(node->head->sibling); // Term
                resolve(node->tail);          // N4
                insert_AST_tail(node->list, node->head->list->head);
                AST_Node* OP1;
                if(node->tail->head->sibling == NULL){

                }
                else {
                    if(node->tail->head->head->symbol->terminal == pLUS){
                        OP1 = create_AST_Node("ADD",NULL);
                    }
                    else {
                        OP1 = create_AST_Node("SUBTRACT",NULL);
                    }
                    insert_AST_tail(node->list,OP1);
                }
                append_AST_lists_tail(node->list, node->head->sibling->list);
                append_AST_lists_tail(node->list, node->tail->list);
            }
        }
        else if (node->symbol->non_terminal == N8)
        {   
            if(node->head->sibling == NULL){

            }
            else {
                resolve(node->head);//RelationalOp
                resolve(node->head->sibling);//ArithmeticExpr
                resolve(node->tail);//N8
                append_AST_lists_tail(node->list,node->head->list);
                AST_Node* REL;
                if(node->tail->head->sibling == NULL){

                }
                else {
                    if(node->tail->head->head->symbol->terminal == lT){
                        REL = create_AST_Node("LT",NULL);
                    }
                    else if(node->tail->head->head->symbol->terminal == lE){
                        REL = create_AST_Node("LE",NULL);
                    }
                    else if(node->tail->head->head->symbol->terminal == gT){
                        REL = create_AST_Node("GT",NULL);
                    }
                    else if(node->tail->head->head->symbol->terminal == gE){
                        REL = create_AST_Node("GE",NULL);
                    }
                    else if(node->tail->head->head->symbol->terminal == eQ){
                        REL = create_AST_Node("EQ",NULL);
                    }
                    else if(node->tail->head->head->symbol->terminal == nE){
                        REL = create_AST_Node("NE",NULL);
                    }
                    insert_AST_tail(node->list,REL);
                }
                append_AST_lists_tail(node->list,node->head->sibling->list);
                append_AST_lists_tail(node->list,node->tail->list);
            }
        }
        else if(node->symbol->non_terminal == RelationalOp){
            resolve(node->head);//lt/le/gt.....
            insert_AST_tail(node->list,node->head->list->head);
        }
        else if (node->symbol->non_terminal == N7)
        {
            if(node->head->sibling == NULL){

            }
            else {
                resolve(node->head);//LogicalalOp
                resolve(node->tail);//N7
                resolve(node->head->sibling);//AnyTerm
                append_AST_lists_tail(node->list,node->head->list);
                AST_Node* LOGIC;
                if(node->tail->head->sibling == NULL){

                }
                else {
                    if(node->tail->head->head->symbol->terminal == aND){
                        LOGIC = create_AST_Node("AND",NULL);
                    }
                    else {
                        LOGIC = create_AST_Node("OR",NULL);
                    }
                    insert_AST_tail(node->list,LOGIC);
                }
                append_AST_lists_tail(node->list,node->head->sibling->list);
                append_AST_lists_tail(node->list,node->tail->list);
            }
        }
        else if(node->symbol->non_terminal == LogicalOp){
            resolve(node->head);//and/or
            insert_AST_tail(node->list,node->head->list->head);
        }
        else if (node->symbol->non_terminal == U)
        {   
            resolve(node->head);//Unary_op
            resolve(node->tail);//New_nt
            insert_AST_tail(node->list,node->head->list->head);
            append_AST_lists_tail(node->list,node->tail->list);
        }
        else if(node->symbol->non_terminal == Unary_op){
            resolve(node->head);//plus/minus
            insert_AST_tail(node->list,node->head->list->head);
        }
        else if (node->symbol->non_terminal == New_NT){
            if(node->head->sibling == NULL){
                resolve(node->head);//var_id_num
                append_AST_lists_tail(node->list,node->head->list);
            }
            else {
                resolve(node->head->sibling);//ArithmeticExpr
                append_AST_lists_tail(node->list,node->head->sibling->list);
            }
        }
        else if(node->symbol->non_terminal == Var_id_num){
            resolve(node->head);//id/num/rnum
            append_AST_lists_tail(node->list,node->head->list);
        }
        else if (node->symbol->non_terminal == LvalueARRStmt)
        {
            AST_Node* ASSIGN = create_AST_Node("ASSIGN",NULL);
            resolve(node->head->sibling);//Element_index_with_expr
            resolve(node->head->sibling->sibling->sibling->sibling);//Expression
            append_AST_lists_tail(node->list,node->head->sibling->list);
            insert_AST_tail(node->list,ASSIGN);
            append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->sibling->list);
        }
        else if (node->symbol->non_terminal == ModuleReuseStmt)
        {
            AST_Node* OPTIONAL = create_AST_Node("FUNCTION_CALL",NULL);
            resolve(node->head);//Optional
            AST_Node* MODULE = create_AST_Node("MODULE", NULL);
            AST_Node* PARAMETERS = create_AST_Node("PARAMETERS",NULL);
            resolve(node->head->sibling->sibling->sibling);//id
            resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling);//Actual_para_list
            insert_AST_tail(node->list,OPTIONAL);
            append_AST_lists_tail(node->list,node->head->list);//optional
            insert_AST_tail(node->list,MODULE);
            insert_AST_tail(node->list,node->head->sibling->sibling->sibling->list->head);//id
            insert_AST_tail(node->list,PARAMETERS);//parameters
            // append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->sibling->sibling->list);
            append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->sibling->sibling->sibling->list);//Actual_para_list
        }
        else if(node->symbol->non_terminal == Optional){
            if(node->head->sibling == NULL){

            }
            else {
                AST_Node* OPTIONAL_LIST = create_AST_Node("OPTIONAL_PARAMETERS",NULL);
                insert_AST_tail(node->list,OPTIONAL_LIST);
                resolve(node->head->sibling);//IDlist
                append_AST_lists_tail(node->list,node->head->sibling->list);
            }
            
        }
        else if(node->symbol->non_terminal ==Actual_para_list){
            resolve(node->head);//Sign_for_loop
            resolve(node->head->sibling);//Actual_para_id
            resolve(node->tail);//Actual_para_list1
            append_AST_lists_tail(node->list,node->head->list);
            append_AST_lists_tail(node->list,node->head->list);
            append_AST_lists_tail(node->list,node->head->sibling->list);
            append_AST_lists_tail(node->list,node->tail->list);
        }
        else if (node->symbol->non_terminal == Actual_para_iD){
            if(node->head->sibling==NULL){
                resolve(node->head);//num/rnum/boolconst
                append_AST_lists_tail(node->list,node->head->list);
            }
            else{
                resolve(node->head);//id
                resolve(node->tail);//N11
                append_AST_lists_tail(node->list,node->head->list);
                append_AST_lists_tail(node->list,node->tail->list);
            }
        }
        else if (node->symbol->non_terminal == Actual_para_list1){
            if(node->head->sibling == NULL){

            }
            else {
                resolve(node->head->sibling);//Sign_for_loop
                resolve(node->head->sibling->sibling);//Actual_para_id
                resolve(node->tail);//ACtual_para_list1
                append_AST_lists_tail(node->list,node->head->sibling->list);
                append_AST_lists_tail(node->list,node->head->sibling->sibling->list);
                append_AST_lists_tail(node->list,node->tail->list);
            }
        }
    }
}

void run_ast(char *prog_file, char *output_file)
{
    run_parser(prog_file, output_file);
    resolve(Parse_Tree_Root->head);
    print_astnodes(Parse_Tree_Root->head);
}

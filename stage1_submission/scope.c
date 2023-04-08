#include "ast.h"

Scope *create_new_scope(int start, int end){
    Scope *scope = (Scope *)malloc(sizeof(Scope));
    scope->end_line = end;
    scope->start_line = start;
    scope->child_scope = NULL;
    scope->parent_scope = NULL;
    scope->sibling_scope = NULL;
    scope->is_a_module = false;
    scope->iplist_offset = 0;
    scope->oplist_offset = 0;
    strcpy(scope->module_name, "");
    return scope;
}

void insert_scope(Scope *scope, Scope *child){
    child->parent_scope = scope;
    if (scope->child_scope == NULL){
        scope->child_scope = child;
    } else {
        Scope *tmp = scope->child_scope;
        while (tmp->sibling_scope != NULL){
            tmp = tmp->sibling_scope;
        }
        tmp->sibling_scope = child;
    }
}

void print_scope(Scope *scope){
    if (scope == NULL){
        printf("SCOPE: NULL\n");
        return;
    }
    printf("SCOPE: IS_A_MODULE: %d, MODULE_NAME: %s, MODULE_IP_OFFSET: %d, MODULE_OP_OFFSET: %d, Start - %d, End - %d\n\n", scope->is_a_module, scope->module_name, scope->iplist_offset, scope->oplist_offset, scope->start_line, scope->end_line);
}

void print_scopes(Scope *scope, char pre[200]){
    char old_pre[200];
    strcpy(old_pre, pre);
    strcat(pre, "   ");
    print_scope(scope);
    if (scope !=NULL && scope->child_scope != NULL){
        printf("%s", pre);
        print_scopes(scope->child_scope, pre);
    }
    if (scope->sibling_scope != NULL){
        printf("%s", old_pre);
        print_scopes(scope->sibling_scope, old_pre);
    }
}

void print_scopes_with_tables(Scope *scope, char pre[200]){
    char old_pre[200];
    strcpy(old_pre, pre);
    strcat(pre, "   ");
    print_scope(scope);
    /* print_symbol_table_element_for_scope(scope->table, pre); */
    print_symbol_table(scope->table);
    if (scope->child_scope != NULL){
        printf("%s", pre);
        print_scopes_with_tables(scope->child_scope, pre);
    }
    if (scope->sibling_scope != NULL){
        printf("%s", old_pre);
        print_scopes_with_tables(scope->sibling_scope, old_pre);
    }
}

TOKEN resolve_scopes(Scope *scope, TOKEN curr, FILE *test_fp){
    while (curr.name != $){
        if (curr.name == sTART){
            Scope *child = create_new_scope(curr.line, -1);
            curr = eval_token(test_fp);
            curr = resolve_scopes(child, curr, test_fp);
            insert_scope(scope, child);
        } 
        else if (curr.name == eND){
            scope->end_line = curr.line;
            return curr;
        }
        if (curr.name == $){
            return curr;
        }
        curr = eval_token(test_fp);
    }
    return curr;
}

Scope *find_scope(Scope *scope, int line){
    if (scope == NULL){
        return GLOBAL_SCOPE;
    }
    if (line > scope->end_line){
        if (scope->sibling_scope == NULL){
            return scope->parent_scope;
        } else {
            return find_scope(scope->sibling_scope, line);
        }
    }
    else if (line < scope->start_line){
        return scope->parent_scope;
    }
    else if (line == scope->start_line || line == scope->end_line){
        return scope;
    }
    else {
        if (scope->child_scope != NULL){
            return find_scope(scope->child_scope, line);
        } else {
            return scope;
        }
    }
}

Scope *find_module_scope(Scope *scope, char module_name[50]){
    if (scope->is_a_module && strcmp(scope->module_name, module_name) == 0){
        return scope;
    } else {
        Scope *found_scope = NULL;
        if (scope->child_scope != NULL){
            found_scope = find_module_scope(scope->child_scope, module_name);
        }
        if (found_scope == NULL && scope->sibling_scope != NULL){
            found_scope = find_module_scope(scope->sibling_scope, module_name);
        }
        return found_scope;
    }
}

void create_scopes(char *prog_file, char *output_file){
    FILE *test_fp = fopen(prog_file, "r");
    lexer_reset(test_fp);
    TOKEN curr;
    curr.name = lEX_ERROR;
    GLOBAL_SCOPE = create_new_scope(0, -1);
    while (curr.name != $) {
        if (curr.name == sTART){
            Scope *scope = create_new_scope(curr.line, -1);
            curr = eval_token(test_fp);
            curr = resolve_scopes(scope, curr, test_fp);
            insert_scope(GLOBAL_SCOPE, scope);
        }
        if (curr.name == $){
            break;
        }
        curr = eval_token(test_fp);
    }
    GLOBAL_SCOPE->end_line = curr.line;
    char prefix[200] = "";
    print_scopes(GLOBAL_SCOPE, prefix);
    printf("\n");
    int line = 61;
    Scope *found_scope = find_scope(GLOBAL_SCOPE, line);
    printf("\n\n    SCOPE AT LINE: %d: \n", line);
    print_scope(found_scope);
}


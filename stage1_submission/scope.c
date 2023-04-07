#include "parser.c"

typedef struct Scope{
    int start_line;
    int end_line;
    struct Scope *child_scope;
    struct Scope *sibling_scope;
    struct Scope *parent_scope;
} Scope;

Scope *create_new_scope(int start, int end){
    Scope *scope = (Scope *)malloc(sizeof(Scope));
    scope->end_line = end;
    scope->start_line = start;
    scope->child_scope = NULL;
    scope->parent_scope = NULL;
    scope->sibling_scope = NULL;
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
    printf("SCOPE: Start %d End %d\n", scope->start_line, scope->end_line);
}

void print_scopes(Scope *scope){
    print_scope(scope);
    if (scope->child_scope != NULL){
        print_scopes(scope->child_scope);
    }
    if (scope->sibling_scope != NULL){
        print_scopes(scope->sibling_scope);
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

void create_scopes(char *prog_file, char *output_file){
    FILE *test_fp = fopen(prog_file, "r");
    lexer_reset(test_fp);
    TOKEN curr;
    curr.name = lEX_ERROR;
    Scope *GLOBAL_SCOPE = create_new_scope(0, -1);
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
    print_scopes(GLOBAL_SCOPE);
}

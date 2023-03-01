#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef PARSE_TREE_LINKED_LIST_INCLUDED
#define PARSE_TREE_LINKED_LIST_INCLUDED
// #include "parser_table.c"
#include "tree_builder.c"
#endif

ErrorList *ERROR_LIST;
LinkedList *Parser_Stack;
TreeNode *Parse_Tree_Root;
TreeNode* curr_node;

void print_error_list(ErrorList *list, FILE *debug_fp){
    printf("\nPRINTING ALL ERRORS CAUGHT > > >\n");
    if (list == NULL || list->head == NULL){
        fprintf(debug_fp, "NO ERRORS - Enjoy your day!\n");
        return;
    }
    Error *curr_error = list->head;
    while (curr_error != NULL){
        fprintf(debug_fp, "\n ERROR DETAILS (LINE - [%d]; TYPE - [%d])\n", curr_error->line, curr_error->type);
        print_token_details(curr_error->token, debug_fp);
        print_symbol_details(curr_error->stack_top, debug_fp);
        curr_error = curr_error->next;
    }
    return;
}
Error *create_new_error(int line, int type, TOKEN token, Symbol *symbol){
    Error *error = (Error *)malloc(sizeof(Error));
    error->line = line;
    error->type = type;
    error->next = NULL;
    error->token = token;
    error->stack_top = symbol;
    return error;
}
ErrorList *create_error_list(){
    ErrorList *list = (ErrorList *)malloc(sizeof(ErrorList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
void insert_error(ErrorList *list, Error *new_error){
    /* Error *new_error = create_new_error(line, type, token, symbol); */
    if (list->head == NULL){
        list->head = new_error;
    } else {
        Error *curr_error = list->head;
        while (curr_error->next != NULL){
            curr_error = curr_error->next;
        }
        curr_error->next = new_error;
    }
    list->size++;
}

void initialize_parser(char *grammar_file){
    printf("Building Grammar (Populating symbols)...\n");
    build_grammar(grammar_file);
    printf("Creating parser tree and stack...\n");
    /* for(int i = 0; i < TOTAL_SYMBOLS; i++){ */
    /*     print_symbol_details(symbols[i], stdout); */
    /*     if (i == 65){ */
    /*         printf("here %p\n", symbols[i]->right); */
    /*         printf("here %p\n", symbols[i]->right->right); */
    /*     } */
    /* } */
    Parse_Tree_Root = create_parse_tree();
    Parser_Stack = create_stack();
    // inserting S initially
    /* Symbol *base = symbols[0]; */
    Parse_Tree_Root->symbol = symbols[0];
    push_stack(Parser_Stack, symbols[0]);
    printf("Generating parse table...\n");
    generate_parse_table();
    parse_table_make();
    update_NT_ROWS();
    ERROR_LIST = create_error_list();
}

void compute_all_symbols(FILE* debug_fp){
    for(int i = 0; i < TOTAL_SYMBOLS; i++){
        symbols[i]->first = compute_first(symbols[i]);
        symbols[i]->follow = compute_follow(symbols[i]);
        print_symbol_details(symbols[i], debug_fp);
    }
    for (int j = 0; j < N_TERMINAL_SYM; j++){
        printf("RULE: %d at row - %d\n", j, NT_TO_ROW[j]);
    }
    /* for(int i = 0; i < TOTAL_SYMBOLS; i++){ */
    /*     Symbol *s = symbols[i]; */
    /*     print_symbol_details(s, debug_fp); */
    /*     fprintf(debug_fp, "\n"); */
    /* } */
}

TOKEN handle_parser_error(TOKEN Curr_Token, Symbol *Top_Symbol, FILE *program_fp, FILE *debug_fp, int error_type){
    Error *created_error = create_new_error(Curr_Token.line, error_type, Curr_Token, Top_Symbol);
    insert_error(ERROR_LIST, created_error);
    if (error_type == 0){
        fprintf(debug_fp, PRINT_RED "\n>>>RECOVERING: Terminal Mismatch\n" PRINT_RESET);

        pop_stack(Parser_Stack);
        curr_node = error_node(curr_node);
        // printf("in handle, curr: %s\n",curr_node->symbol->name);
        fprintf(debug_fp, PRINT_BLUE "\n<<<RECOVERED: Stack terminal popped\n" PRINT_RESET);
        return Curr_Token;
    } else if (error_type == 1){
        fprintf(debug_fp, PRINT_RED "\n>>>RECOVERING: No Rule found in Parser Table\n" PRINT_RESET);
        print_symbol_details(Top_Symbol, debug_fp);

        // Strategy 1 - Follow Set as Sync Set
        // while ((Curr_Token.name != $) && (find_node(term_str[Curr_Token.name], Top_Symbol->follow) == 0)){ 
        //     fprintf(debug_fp, "\n...RECOVERING:"); 
        //     print_token_details(Curr_Token, debug_fp); 
        //     print_symbol_details(Top_Symbol, debug_fp);
        //     Curr_Token = eval_token(program_fp); 
        // } 
        // if (Curr_Token.name != $){ 
        //     fprintf(debug_fp, "\n>>>RECOVERED, Stack Non Terminal popped\n"); 
        //     pop_stack(Parser_Stack);
        //     curr_node = error_node(curr_node); 
        // } 

        // Strategy 2 - First Set as Sync Set
        while ((Curr_Token.name != $) && (find_node(term_str[Curr_Token.name], Top_Symbol->first) == 0)){
            fprintf(debug_fp, PRINT_RED "\n...RECOVERING:" PRINT_RESET);
            print_token_details(Curr_Token, debug_fp);
            print_symbol_details(Top_Symbol, debug_fp);
            Curr_Token = eval_token(program_fp);
        }
        if (Curr_Token.name != $){
            fprintf(debug_fp, PRINT_BLUE "\n<<<RECOVERED, some file tokens skipped\n" PRINT_RESET);
        }
        return Curr_Token;
    }
    return Curr_Token;
}

void parse_next(TOKEN Curr_Token, FILE *program_fp,  FILE *debug_fp){
    int c = 0;
    /* while (is_empty_stack(Parser_Stack) == 0){ // actually curr token !+ EOF */
    while (c != 2500 && is_empty_stack(Parser_Stack) == 0){
        c++;
        printf("sdf %d\n", c);
        Symbol *Top_Symbol = top_stack(Parser_Stack);   
        LinkedList *Aux_Stack = create_stack();

        fprintf(debug_fp, "\n    CURR STACK TOP: IS_T - %d; # - T/F? - %d; ENUM - %d:", Top_Symbol->is_terminal,
           strcmp(Top_Symbol->name, "#"), Top_Symbol->is_terminal ? Top_Symbol->terminal : Top_Symbol->non_terminal);
        // ignore lexical errors TODO: test this
        // print_stack(Parser_Stack, debug_fp);
        fprintf(debug_fp, "    ");
        // print_token_details(Curr_Token, debug_fp);
        if (Curr_Token.name == lEX_ERROR){
            fprintf(debug_fp, PRINT_RED "LEXICAL ERROR: Found\n" PRINT_RESET);
            Curr_Token = eval_token(program_fp);
            /* printf("\n after error NEW TOKEN - line - %d, type - %d, id - %s, num - %d, rnum - %f",  */
            /*    Curr_Token.line, Curr_Token.name, Curr_Token.id, Curr_Token.num, Curr_Token.rnum); */
            continue;
        }
        else if (Curr_Token.name == $){
            fprintf(debug_fp, PRINT_RED "\nFILE EOF ERROR: Stack non empty, Found\n" PRINT_RESET);
            break;
        }
        else if (Top_Symbol->is_terminal == 1){
            if (strcmp(Top_Symbol->name, "#") == 0){
                fprintf(debug_fp, PRINT_BLUE "DEBUG: Found #\n" PRINT_RESET);
                pop_stack(Parser_Stack);
                curr_node = next_node(curr_node,Top_Symbol); 
                continue;
            } 
            else if (Top_Symbol->terminal == Curr_Token.name){
                fprintf(debug_fp, PRINT_GREEN "DEBUG: Matched Terminal: %d\n" PRINT_RESET, Curr_Token.name);
                pop_stack(Parser_Stack);
                curr_node = next_node(curr_node,Top_Symbol); 
                Curr_Token = eval_token(program_fp);
                /* printf("\n NEW TOKEN - line - %d, type - %d, id - %s, num - %d, rnum - %f",  */
                /*    Curr_Token.line, Curr_Token.name, Curr_Token.id, Curr_Token.num, Curr_Token.rnum); */
            } 
            else {
                fprintf(debug_fp, PRINT_RED "ERROR: Terminals Don't Match! (STACK TERM: %d, TOKEN: %d)\n" PRINT_RESET, Top_Symbol->terminal, Curr_Token.name);
                Curr_Token = handle_parser_error(Curr_Token, Top_Symbol, program_fp, debug_fp, 0);
                printf("\nholaaaaaaaaa\n");
                /* break; */
            }
        } 
        else if (Top_Symbol->is_terminal == 0){
            Symbol* Grammar_Rule = parser_table[Top_Symbol->non_terminal][Curr_Token.name];
            if (Grammar_Rule != NULL){
                fprintf(debug_fp, PRINT_GREEN "DEBUG: Found Rule >>> \n" PRINT_RESET);
                // print_symbol_details(Grammar_Rule, debug_fp);
                // popping from stack
                pop_stack(Parser_Stack);
                curr_node = next_node(curr_node,Grammar_Rule); 

                Symbol *curr = Grammar_Rule->right;
                while (curr != NULL){
                    push_stack(Aux_Stack, curr);
                    curr = curr->right;
                }
                
                while (!is_empty_stack(Aux_Stack)){
                    curr = top_stack(Aux_Stack);
                    /* fprintf(debug_fp, "\nunpusing"); */
                    /* print_symbol_details(curr, debug_fp); */
                    push_stack(Parser_Stack, curr);
                    pop_stack(Aux_Stack);
                }
                /* int rule_length = get_length(Grammar_Rule); */
                /* printf("Rule Length: %d <<<\n", rule_length); */
                
            } else {
                fprintf(debug_fp, PRINT_RED "ERROR: No rule found in parser table! (STACK NT: %d, TOKEN: %d)\n" PRINT_RESET, Top_Symbol->non_terminal, Curr_Token.name);
                Top_Symbol->first = symbols[NT_TO_ROW[Top_Symbol->non_terminal]]->first;
                Top_Symbol->follow = symbols[NT_TO_ROW[Top_Symbol->non_terminal]]->follow;
                // print_symbol_details(Top_Symbol, debug_fp);
                Curr_Token = handle_parser_error(Curr_Token, Top_Symbol, program_fp, debug_fp, 1);
                /* break; */
            }
        }
        // fprintf(debug_fp, "Curr: %s\n\n",Curr_Token.id);
    }
    fprintf(debug_fp, PRINT_CYAN "\nPARSING COMPLETE.\n" PRINT_RESET);
}

void start_parsing(char *program_file, FILE *debug_fp){
    char* uncommented = "program.txt";
    FILE* program_fp = fopen(program_file, "r");
    remove_comments(program_fp, uncommented);
    program_fp = fopen(uncommented, "r");
    lexer_reset(program_fp);
    fprintf(debug_fp, "Lexer setup complete\n");
    TOKEN Curr_Token = eval_token(program_fp);
    curr_node = Parse_Tree_Root;
    parse_next(Curr_Token, program_fp, debug_fp);
}


int main(){
    char *grammar_file = "../grammar.txt";
    char *debug_file = "parser_output.txt";
    char *debug_tree_file = "parser_output_tree.txt";
    initialize_parser(grammar_file);
    // starting lexer
    printf("\n\nStarting lexer...\n");
    char *program_file = "../tests/test_cases_stage_1/t6_syntax_errors.txt"; 
    // char *program_file = "../tests/test_lexer_1.txt";
    printf("Starting parsing...\n");
    FILE *debug_fp = fopen(debug_file, "w");
    FILE *debug_tree_fp = fopen(debug_tree_file, "w");

    // compute_all_symbols(stdout);

    start_parsing(program_file, stdout);
    print_error_list(ERROR_LIST, stdout);
    printf("Printing tree\n");
    printParseTree(Parse_Tree_Root, debug_tree_fp);
}

/* int main(){ */
/*     char *grammar_file = "../grammar.txt"; */
/*     build_grammar(grammar_file); */
/*     printf("\n"); */
/*     TreeNode *root = create_parse_tree(); */
/*     root->symbol = symbols[0]; */
/*     insert_child(root, root->symbol); // S */
/*     insert_child(root->head, symbols[1]); // Program */
/*     insert_child(root->head->head, symbols[2]); // ModuleDeclarations */
/*     insert_child(root->head->head->head, symbols[4]); // OtherModules */
/*     print_tree(root); */
/*     return 0; */
/* } */
/*  */

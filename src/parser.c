#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef PARSE_TREE_LINKED_LIST_INCLUDED
#define PARSE_TREE_LINKED_LIST_INCLUDED
#include "parser_table.c"
#endif

LinkedList *Parser_Stack;
TreeNode *Parse_Tree_Root;

void initialize_parser(char *grammar_file){
    printf("Building Grammar (Populating symbols)...\n");
    build_grammar(grammar_file);
    printf("Creating parser tree and stack...\n");
    /* for(int i = 0; i < TOTAL_SYMBOLS; i++){ */
    /*     print_symbol_details(symbols[i], NULL); */
    /*     if (i == 65){ */
    /*         printf("here %p\n", symbols[i]->right); */
    /*         printf("here %p\n", symbols[i]->right->right); */
    /*     } */
    /* } */
    Parse_Tree_Root = create_parse_tree();
    Parser_Stack = create_stack();
    // inserting S initially
    Symbol *base = symbols[0];
    Parser_Stack = push_stack(Parser_Stack, base);
    printf("Generating parse table...\n");
    generate_parse_table();
    parse_table_make();
}

void start_parsing(char *program_file, FILE *debug_fp){
    char* uncommented = "program.txt";
    FILE* program_fp = fopen(program_file, "r");
    remove_comments(program_fp, uncommented);
    program_fp = fopen(uncommented, "r");
    lexer_reset(program_fp);
    if (debug_fp == NULL){
        printf("Lexer setup complete\n");
    } else {
        fprintf(debug_fp, "Lexer setup complete\n");
    }
    TOKEN Curr_Token = eval_token(program_fp);

    int c = 0;
    while (is_empty_stack(Parser_Stack) == 0){ // actually curr token !+ EOF
    /* while (c != 220){ */
        c++;
        Symbol *Top_Symbol = top_stack(Parser_Stack);    
        LinkedList *Aux_Stack = create_stack();
        if (debug_fp == NULL){
            printf("\n    CURR STACK TOP: IS_T - %d; # - T/F? - %d; ENUM - %d:", Top_Symbol->is_terminal,
               strcmp(Top_Symbol->name, "#"), Top_Symbol->is_terminal ? Top_Symbol->terminal : Top_Symbol->non_terminal);
        } else {
            fprintf(debug_fp, "\n    CURR STACK TOP: IS_T - %d; # - T/F? - %d; ENUM - %d:", Top_Symbol->is_terminal,
               strcmp(Top_Symbol->name, "#"), Top_Symbol->is_terminal ? Top_Symbol->terminal : Top_Symbol->non_terminal);
        }
        // ignore lexical errors TODO: test this
        if (Curr_Token.name == lEX_ERROR){
            Curr_Token = eval_token(program_fp);
            continue;
        }
        print_stack(Parser_Stack, debug_fp);
        print_token_details(Curr_Token, debug_fp);
        if (Top_Symbol->is_terminal){
            if (strcmp(Top_Symbol->name, "#") == 0){
                if (debug_fp == NULL){
                    printf("DEBUG: Found #\n");
                } else {
                    fprintf(debug_fp, "DEBUG: Found #\n");
                }
                pop_stack(Parser_Stack);
                continue;
            } 
            else if (Top_Symbol->terminal == Curr_Token.name){
                if (debug_fp == NULL){
                    printf("DEBUG: Matched Terminal: %d\n", Curr_Token.name);
                } else {
                    fprintf(debug_fp, "DEBUG: Matched Terminal: %d\n", Curr_Token.name);
                }
                pop_stack(Parser_Stack);
                Curr_Token = eval_token(program_fp);
            } 
            else {
                if (debug_fp == NULL){
                    printf("ERROR: Terminals Don't Match! (STACK TERM: %d, TOKEN: %d)\n", Top_Symbol->terminal, Curr_Token.name);
                } else {
                    fprintf(debug_fp, "ERROR: Terminals Don't Match! (STACK TERM: %d, TOKEN: %d)\n", Top_Symbol->terminal, Curr_Token.name);
                }
                break;
            }
        } else{
            Symbol* Grammar_Rule = parser_table[Top_Symbol->non_terminal][Curr_Token.name];
            if (Grammar_Rule != NULL){
                if (debug_fp == NULL){
                    printf("DEBUG: Found Rule >>> \n");
                } else {
                    fprintf(debug_fp, "DEBUG: Found Rule >>> \n");
                }
                print_symbol_details(Grammar_Rule, debug_fp);
                // popping from stack
                pop_stack(Parser_Stack);
                Symbol *curr = Grammar_Rule->right;
                while (curr != NULL){
                    push_stack(Aux_Stack, curr);
                    curr = curr->right;
                }
                while (!is_empty_stack(Aux_Stack)){
                    curr = top_stack(Aux_Stack);
                    push_stack(Parser_Stack, curr);
                    pop_stack(Aux_Stack);
                }
                /* int rule_length = get_length(Grammar_Rule); */
                /* printf("Rule Length: %d <<<\n", rule_length); */
            } else {
                if (debug_fp == NULL){
                    printf("ERROR: No rule found in parser table! (STACK NT: %d, TOKEN: %d)\n", Top_Symbol->non_terminal, Curr_Token.name);
                } else {
                    fprintf(debug_fp, "ERROR: No rule found in parser table! (STACK NT: %d, TOKEN: %d)\n", Top_Symbol->non_terminal, Curr_Token.name);
                }
                break;
            }
        }
    }
    if (debug_fp == NULL){
        printf("\nPARSING COMPLETE.\n");
    } else {
        fprintf(debug_fp, "\nPARSING COMPLETE.\n");
    }
}

int main(){
    char *grammar_file = "../grammar.txt";
    char *debug_file = "parser_output.txt";
    initialize_parser(grammar_file);
    // starting lexer
    printf("\n\nStarting lexer...\n");
    char *program_file = "../tests/test_lexer_7.txt";
    printf("Starting parsing...\n");
    FILE *debug_fp = fopen(debug_file, "w");
    start_parsing(program_file, NULL);
}

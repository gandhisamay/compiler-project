#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef PARSE_TREE_LINKED_LIST_INCLUDED
#define PARSE_TREE_LINKED_LIST_INCLUDED
#include "parser_table.c"
#endif

FILE *program_fp;
LinkedList *Parser_Stack;
TreeNode *Parse_Tree_Root;

void initialize_parser(){
    printf("Building Grammar (Populating symbols)...\n");
    build_grammar();
    printf("Creating parser tree and stack...\n");
    Parse_Tree_Root = create_parse_tree();
    Parser_Stack = create_stack();
    printf("Generating parse table...\n");
    generate_parse_table();
    parse_table_make();
}

void start_parsing(){
    Symbol *Top_Symbol = top_stack(Parser_Stack);    
    print_symbol_details(Top_Symbol);
    /* pop_stack(Parser_Stack); // removing initial '$' */
    TOKEN Curr_Token = eval_token(program_fp);
    print_token_details(Curr_Token, NULL);
    /* print_stack(Parser_Stack); */
    Curr_Token = eval_token(program_fp);
    print_token_details(Curr_Token, NULL);
    /* print_lt(Lookup_Table); */
    /* Symbol* Grammar_Rule = parser_table[Top_Symbol->non_terminal][Curr_Token.name]; */
    /* if (Grammar_Rule != NULL){ */
    /*     print_symbol_details(Grammar_Rule); */
    /* } */
}

int main(){
    initialize_parser();
    // starting lexer
    printf("\n\nStarting lexer...\n");
    char *program_file = "../tests/test_lexer_1.txt";
    program_fp = fopen(program_file, "r");
    lexer_reset(program_fp);
    printf("Starting parsing...\n");
    start_parsing();
}

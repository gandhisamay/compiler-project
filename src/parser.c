#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* #ifndef LEXER_INCLUDED */
/* #define LEXER_INCLUDED  */
/* #include "lexer_helper.h" */
/* #endif */
#ifndef PARSE_TREE_LINKED_LIST_INCLUDED
#define PARSE_TREE_LINKED_LIST_INCLUDED
#include "parser_table.c"
#endif

void initialize_parser(){
    printf("Creating parser tree and stack\n");
    ParseTree = create_parse_tree();    
    ParserStack = create_stack();
}

int main(){
    initialize_parser();
}

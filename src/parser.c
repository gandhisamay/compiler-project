#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.c"

void initialize_parser(){
    ParseTree = create_parse_tree();    
    ParserStack = create_stack();
}

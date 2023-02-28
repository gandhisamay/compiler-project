/* #include "linked_list.h" */
/* #include "lexer_helper.h" */
#include "lexer.c"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* int GRAMMAR_SIZE = 0; */
/* int RULE_WIDTH = 512; */
/* int TOTAL_SYMBOLS = 0; */
/* int MAX_SYMBOLS_ARRAY_SIZE = 64; */
/* char **grammar; */
/* Symbol *symbols[256]; */
/*  */
/* char **read_grammar_file(char *file) { */
/*   int ROW_TOTAL = 16; */
/*   int COL_TOTAL = 128; */
/*   char **array; */
/*  */
/*   array = (char **)malloc(ROW_TOTAL * sizeof(char *)); // 4 */
/*   for (int i = 0; i < ROW_TOTAL; i++) */
/*     array[i] = (char *)malloc(COL_TOTAL * sizeof(char)); // 32 */
/*  */
/*   FILE *fp; */
/*   fp = fopen(file, "r"); */
/*   if (fp != NULL) { */
/*     char buff[1024]; */
/*     while (fgets(buff, 1024, fp)) { */
/*       int size_row = COL_TOTAL; */
/*       int col_no = 0; */
/*  */
/*       char *tok = strtok(buff, "\n"); */
/*       if (tok == NULL) */
/*         break; */
/*       int size = (strlen(tok) + 2); */
/*       char *memory = (char *)malloc(size * sizeof(char)); */
/*       strcpy(memory, tok); */
/*       memory[size - 2] = ' '; */
/*       memory[size - 1] = '\0'; */
/*       array[GRAMMAR_SIZE] = memory; */
/*       GRAMMAR_SIZE++; */
/*     } */
/*  */
/*   } else { */
/*     printf("Failed to open file!\n"); */
/*     exit(EXIT_FAILURE); */
/*   } */
/*  */
/*   return array; */
/* } */
/*  */
/* void build_grammar() { */
/*   // grammar = read_file("dummy_grammar1.txt"); */
/*   grammar = read_grammar_file("grammar.txt"); */
/*   // */
/*   printf("%d", GRAMMAR_SIZE); */
/*  */
/*   for (int i = 0; i < GRAMMAR_SIZE; i++) { */
/*     printf("%s\n", grammar[i]); */
/*   } */
/*  */
/*   // find symbols from this. */
/*   Symbol *prev = NULL; */
/*   for (int i = 0; i < GRAMMAR_SIZE; i++) { */
/*     int j = 0; */
/*     int sz = 0; */
/*     int symbols_for_current_row = 0; */
/*  */
/*     char symbol_name[32] = {'@'}; */
/*     while (grammar[i][j] != '\0') { */
/*       if (!isspace(grammar[i][j])) { */
/*         symbol_name[sz] = grammar[i][j]; */
/*         sz++; */
/*       } else { */
/*         if (symbol_name[0] == '=') { */
/*           sz = 0; */
/*           j++; */
/*           continue; */
/*         } */
/*  */
/*         Symbol *new = (Symbol *)malloc(sizeof(Symbol)); */
/*  */
/*         new->name = (char *)malloc(sz * sizeof(char)); */
/*         for (int k = 0; k < sz; k++) */
/*           new->name[k] = symbol_name[k]; */
/*  */
/*         // need to create the linked list first. */
/*         new->first = create_linked_list(); */
/*         new->follow = create_linked_list(); */
/*         new->row_no = i; */
/*  */
/*         if (prev != NULL && prev->row_no == new->row_no) { */
/*           prev->right = new; */
/*         } */
/*  */
/*         if (isupper(symbol_name[0])) */
/*           new->is_terminal = false; */
/*         else */
/*           new->is_terminal = true; */
/*  */
/*         prev = new; */
/*         // TODO: Do dynamic memory allocation here. */
/*  */
/*         if (symbols_for_current_row == 0) { */
/*           symbols_for_current_row++; */
/*           symbols[TOTAL_SYMBOLS] = new; */
/*           TOTAL_SYMBOLS++; */
/*         } */
/*         sz = 0; */
/*       } */
/*       j++; */
/*     } */
/*     symbols_for_current_row = 0; */
/*   } */
/* } */
/*  */

// stack functions start

LinkedList* push_stack(LinkedList* stack, Symbol* s){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->symbol = s;
    if(stack->head == NULL){
        stack->head = temp;
        temp->next = NULL;
        stack->tail = temp;
    } else {
        stack->tail->next = temp;
        stack->tail = temp;
        stack->tail->next = NULL;
    }
    return stack;
}

bool is_empty_stack(LinkedList* stack){
    if(stack->head == NULL && stack->tail == NULL)
        return true;
    return false;
}

LinkedList* pop_stack(LinkedList* stack){
    if(!is_empty_stack(stack)){
        Node* curr = stack->head;
        if(curr == stack->tail){
            free(stack->head);
            stack->head = NULL;
            stack->tail = NULL;
            return stack;
        }
        while(curr->next != stack->tail)
            curr = curr->next;
        Node * temp;
        temp = curr->next;
        stack->tail = curr;
        curr->next = NULL;
        free(temp);
    }
    return stack;
}

Symbol* top_stack(LinkedList* stack){
    return stack->tail->symbol;
}

LinkedList* create_stack(){
    LinkedList *stack = (LinkedList *) malloc(sizeof(LinkedList));
    Symbol *base = (Symbol *) malloc(sizeof(Symbol));
    return stack;
}

void print_stack(LinkedList *stack, FILE* debug_fp){
    if (debug_fp == NULL) printf("\nCurrent Stack: [Bottom] -> ");
    else fprintf(debug_fp, "\nCurrent Stack: [Bottom] -> ");
    Node *curr = stack->head;
    while(curr != NULL){
        if (debug_fp == NULL) printf("%s -> ", curr->symbol->name);
        else fprintf(debug_fp, "%s -> ", curr->symbol->name);
        curr = curr->next;
    }
    if (debug_fp == NULL) printf("[Top]\n");
    else printf("[Top]\n");
}

// stack functions end

/* int main(){  */
/*     build_grammar(); */
/*     printf("\n"); */
/*     LinkedList *s = create_stack(); */
/*     print_stack(s); */
/*     push_stack(s, symbols[4]); */
/*     push_stack(s, symbols[5]); */
/*     push_stack(s, symbols[6]); */
/*     print_stack(s); */
/*     printf("%s\n",top_stack(s)->name); */
/*     pop_stack(s); */
/*     pop_stack(s); */
/*     print_stack(s); */
/*     pop_stack(s); */
/*     pop_stack(s); */
/*     print_stack(s); */
/*     printf("%d\n",is_empty_stack(s)); */
/* } */

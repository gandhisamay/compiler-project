/*
 * Group 22
 * Samay Gandhi 2020A7PS0299P
 * Mohit Makwana 2020A7PS0048P
 * Kathan Patel 2020A7PS0058P
 * Aditya Sheth 2020A7PS1511P
 * Aryan Chavan 2020A7PS1692P
 */

#include "Stack.c"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* int GRAMMAR_SIZE = 0; */
/* int RULE_WIDTH = 512; */
/* int TOTAL_SYMBOLS = 0; */
/* int MAX_SYMBOLS_ARRAY_SIZE = 64; */
/* char **grammar; */
/* Symbol *symbols[256]; */
// TreeNode *current, *previous, *terminal_head;
/*  */
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

// parse tree start
/*
@brief : Creates a new parse tree
@input : void
@output : Treenode*
*/
TreeNode *create_parse_tree() {
  TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
  root->head = NULL;
  root->tail = NULL;
  root->sibling = NULL;
  root->symbol = NULL;
  return root;
}

/*
@brief : Create a new node
@input : void
@output : Treenode*
*/
TreeNode *create_treeNode() {
  TreeNode *x = (TreeNode *)malloc(sizeof(TreeNode));
  x->head = NULL;
  x->tail = NULL;
  x->sibling = NULL;
  x->symbol = NULL;
  x->list = NULL;
  x->node_type = NULL;
  /* x->token = NULL; */
  return x;
}

/*
@brief : Insert new children in tree at given node
@input : Treenode* , Symbol*
@output : Treenode*
*/
void insert_child(TreeNode *parent,
                  Symbol *symbol) { // pointer to parent, and LHS of grammar
  print_symbol_info(parent->symbol, stdout);
  if (strcmp(parent->symbol->name, symbol->name) ==
      0) { // A -> B C => parent = A, LHS = A
    Symbol *sym = symbol->right;
    while (sym != NULL) {
      TreeNode *curr = create_treeNode();
      curr->symbol = sym;
      if (parent->head == NULL && parent->tail == NULL) {
        parent->head = curr;
        parent->tail = curr;
        curr->parent = parent;
      } else {
        parent->tail->sibling = curr;
        parent->tail = curr;
        curr->parent = parent;
      }

      // if(curr->symbol->is_terminal){
      //   if(current == NULL && previous == NULL){
      //     terminal_head = curr;
      //     current = curr;
      //     previous = curr;
      //     current->sibling = NULL;
      //   } else {
      //     current = curr;
      //     previous->sibling = current;
      //     previous = current;
      //     current->sibling = NULL;
      //   }
      // }

      sym = sym->right;
    }
  } else
    printf("The parent and given LHS do not match!!!!!!!!!!!!\n");
}

// void print_tree(TreeNode *root, FILE *debug_fp)
// {
//   fprintf(debug_fp, " %s => ", root->symbol->name);
//   TreeNode *curr = root->head;
//   while (curr != NULL)
//   {
//     fprintf(debug_fp, "%s ", curr->symbol->name);
//     curr = curr->sibling;
//   }
//   fprintf(debug_fp, "[END]");
//   fprintf(debug_fp, "\n");
//   curr = root->head;
//   while (curr != NULL)
//   {
//     if (curr->head != NULL)
//     {
//       print_tree(curr, debug_fp);
//     }
//     else if (curr->symbol->is_terminal)
//     {
//       curr = curr->sibling;
//       continue;
//     }
//     else
//     {
//       break;
//     }
//     curr = curr->sibling;
//   }
// }

// @TODO: change to astnode
void print_astnode_details(AST_Node *node, FILE *debug_fp) {
  if (node == NULL){
    fprintf(debug_fp, "\nAST: NULL\n");
    return;
  }
  fprintf(debug_fp, "\nLabel: %s \n", node->label);
  if (node->token_set) print_token_details(node->token, debug_fp);
  Symbol *s = node->data;
  if (s != NULL){
      fprintf(debug_fp, "DATA: Name: %s ", s->name);
      fprintf(debug_fp, "Enum_T: %d, Enum_NT: %d, ", s->terminal, s->non_terminal);
      fprintf(debug_fp, "IS_A: %s\n", s->is_terminal ? "Terminal" : "Non Terminal");
      /* fprintf(debug_fp, "First: "); */
      /* print_list(s->first, debug_fp); */
      /* fprintf(debug_fp, "Follow: "); */
      /* print_list(s->follow, debug_fp); */
      /* fprintf(debug_fp, "Right: [HEAD] -> "); */
      /*  */
      /* Symbol *temp = s->right; */
      /* while (temp != NULL) { */
      /*   fprintf(debug_fp, "%s -> ", temp->name); */
      /*   temp = temp->right; */
      /* } */
      /* fprintf(debug_fp, "[END]\n"); */
  } else {
    fprintf(debug_fp, "No data\n"); 
  }
}

/*
@brief : Prints parse tree in inorder traversal
@input : Treenode* , FILE*
@output : void
*/
void printParseTree(TreeNode *root, FILE *outfile) {
  if (root != NULL) {
    printParseTree(root->head, outfile);

    fprintf(outfile, "==============>  ");
    /* print_astnode_details(root, outfile); */
    print_symbol_details(root->symbol, outfile);
    print_token_details(root->token, outfile);
    // print_symbol_info(root->symbol, outfile);
    fprintf(outfile, "\n\n");

    if (root->head != NULL) {
      TreeNode *curr = root->head;
      curr = curr->sibling;
      while (curr != NULL) {
        printParseTree(curr, outfile);
        curr = curr->sibling;
      }
    }
  }
}

// void print_terminal_list(){
//   current = terminal_head;
//   printf("[HEAD] -> ");
//   while(current != NULL){
//     printf("%s -> ", current->symbol->name);
//     current = current->sibling;
//   }
//   printf("[END]\n");
// }

// parse tree functions end
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

TreeNode *error_node(TreeNode *node) {
  // printf("in error, pre: %s\n",node->symbol->name);
  bool node_found = false;
  if (node == NULL)
    return node;
  // printf("in error, pre: %s\n",node->symbol->name);
  if (node->sibling != NULL) {
    node = node->sibling;
    node_found = true;
  } else {
    while (!node_found) {
      node = node->parent;
      if (node == NULL)
        return node;
      if (node->sibling != NULL) {
        node = node->sibling;
        node_found = true;
      }
    }
  }
  printf("in error, new: %s\n", node->symbol->name);
  return node;
}

TreeNode *next_node(TreeNode *node, Symbol *sym) {
  // print_symbol_details(sym,stdout);
  bool node_found = false;
  // printf("in next, pre: %s\n",node->symbol->name);
  // printf("in next, sym: %s\n",sym->name);
  if (node == NULL|| node->symbol->terminal == $) {

    node = NULL;
  } else if (node->symbol->is_terminal) {
    // print_symbol_details(sym,stdout);

    if (node->sibling != NULL) {
      node = node->sibling;
      node_found = true;
    } else
      while (!node_found) {
        node = node->parent;
        if (node == NULL)
          return node;
        if (node->sibling != NULL) {
          node = node->sibling;
          node_found = true;
        }
      }
  } else {

    insert_child(node, sym);
    node = node->head;
    node_found = true;
    // printf("node: %s\n",node->symbol->name);
  }
  // printf("in next, new: %s\n",node->symbol->name);
  return node;
}

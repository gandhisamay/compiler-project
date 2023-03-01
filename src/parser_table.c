#include "parse_tree.c"
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
/* LinkedList **data; */
/* Symbol*** parser_table; */

/* enum terminals{dECLARE,$,mODULE,iD,iN,sEMICOL,dRIVERDEF,dRIVER,pROGRAM,dRIVERENDDEF,dEF,eNDDEF,tAKES,iNPUT,sQBO,sQBC,rETURNS,cOLON,cOMMA,iNTEGER,rEAL,bOOLEAN,aRRAY,oF,sTART,eND,gET_VALUE,bO,bC,pRINT,tRUE,fALSE,nUM,rNUM,aSSIGNOP,uSE,wITH,pARAMETERS, */
/* pLUS,mINUS,mUL,dIV,aND,oR,lT,lE,gT,gE,eQ,nE,sWITCH,cASE,bREAK,dEFAULT,fOR,wHILE,rANGEOP, TERMINAL_SYM, lEX_ERROR}; */
/*  */
/* char *term_str[] = {"$","dECLARE","mODULE","iD","sEMICOL","dRIVERDEF","dRIVER","pROGRAM","dRIVERENDDEF","dEF","eNDDEF","tAKES","iNPUT","sQBO","sQBC","rETURNS","cOLON","cOMMA","iNTEGER","rEAL","bOOLEAN","aRRAY","oF","sTART","eND","gET_VALUE", */
/* "bO","bC","pRINT","tRUE","fALSE","nUM","rNUM","aSSIGNOP","uSE","wITH","pARAMETERS"," pLUS","mINUS","mUL","dIV","aND","oR","lT","lE","gT","gE","eQ","nE","sWITCH","cASE","bREAK","dEFAULT","fOR","wHILE","rANGEOP"}; */
/*  */
/*  */
/* enum n_terminals{S,Program,ModuleDeclarations,ModuleDeclaration,OtherModules,DriverModule,Module,Ret,Input_plist,Inpl_1,Output_plist,Onpl_1,DataType,Type,ModuleDef,Statements,Statement,IoStmt,Var,BoolConstt,Var_id_num,WhichId,SimpleStmt,AssignmentStmt,WhichStmt,LvalueiDStmt,LvalueARRStmt,Index,ModuleReuseStmt,Optional,IdList,Idl_1,Expression,U,New_NT,Unary_op,ArithmeticOrBooleanExpr,ArxBool_1,AnyTerm,AnyTerm_1,ArithmeticExpr,Arx_1,Term,Term_1,Factor,Op1,Op2,LogicalOp,RelationalOp,DeclareStmt,ConditionalStmt,CaseStmts, */
/* CaseStmt,Value,Default,IterativeStmt,Range,Range_Index,Range_Array,Array_Index, N_TERMINAL_SYM}; */
/*  */
/* char *n_term_str[] = {"S","Program","ModuleDeclarations","ModuleDeclaration","OtherModules","DriverModule","Module","Ret","Input_plist","Inpl_1","Output_plist","Onpl_1","DataType","Type","ModuleDef","Statements","Statement","IoStmt","Var","BoolConstt","Var_id_num","WhichId", */
/* "SimpleStmt","AssignmentStmt","WhichStmt","LvalueiDStmt","LvalueARRStmt","Index","ModuleReuseStmt","Optional","IdList","Idl_1","Expression","U","New_NT","Unary_op","ArithmeticOrBooleanExpr","ArxBool_1","AnyTerm","AnyTerm_1","ArithmeticExpr","Arx_1","Term","Term_1","Factor","Op1","Op2","LogicalOp","RelationalOp","DeclareStmt", */
/* "ConditionalStmt","CaseStmts","CaseStmt","Value","Default","IterativeStmt","Range","Range_Index","Range_Array","Array_Index"}; */

char **read_grammar_file(char *file) {
  int ROW_TOTAL = 16;
  int COL_TOTAL = 128;
  char **array;

  array = (char **)malloc(ROW_TOTAL * sizeof(char *)); // 4
  for (int i = 0; i < ROW_TOTAL; i++)
    array[i] = (char *)malloc(COL_TOTAL * sizeof(char)); // 32

  FILE *fp;
  fp = fopen(file, "r");
  if (fp != NULL) {
    char buff[1024];
    while (fgets(buff, 1024, fp)) {
      int size_row = COL_TOTAL;
      int col_no = 0;

      char *tok = strtok(buff, "\n");
      if (tok == NULL)
        break;
      int size = (strlen(tok) + 2);
      char *memory = (char *)malloc(size * sizeof(char));
      strcpy(memory, tok);
      memory[size - 2] = ' ';
      memory[size - 1] = '\0';
      array[GRAMMAR_SIZE] = memory;
      GRAMMAR_SIZE++;
    }

  } else {
    printf("Failed to open file!\n");
    exit(EXIT_FAILURE);
  }

  return array;
}

void print_symbol_details(Symbol *s, FILE *debug_fp) {
    if (debug_fp == NULL){
      printf("Name: %s, ", s->name);
      printf("Enum_T: %d, Enum_NT: %d, ", s->terminal, s->non_terminal);
      printf("IS_A: %s\n", s->is_terminal ? "Terminal" : "Non Terminal");
      printf("First: ");
      print_list(s->first, NULL);
      printf("Follow: ");
      print_list(s->follow, NULL);
      printf("Right: [HEAD] -> ");
    } else {
      fprintf(debug_fp, "Name: %s, ", s->name);
      fprintf(debug_fp, "Enum_T: %d, Enum_NT: %d, ", s->terminal, s->non_terminal);
      fprintf(debug_fp, "IS_A: %s\n", s->is_terminal ? "Terminal" : "Non Terminal");
      fprintf(debug_fp, "First: ");
      print_list(s->first, debug_fp);
      fprintf(debug_fp, "Follow: ");
      print_list(s->follow, debug_fp);
      fprintf(debug_fp, "Right: [HEAD] -> ");
    }

  Symbol *temp = s->right;
  while (temp != NULL) {
    if (debug_fp == NULL) printf("%s -> ", temp->name);
    else fprintf(debug_fp, "%s -> ", temp->name);
    temp = temp->right;
  }
  if (debug_fp == NULL) printf("[END]\n");
  else fprintf(debug_fp, "[END]\n");

  if (debug_fp == NULL) printf("Row no: %d\n", s->row_no);
  else fprintf(debug_fp, "Row no: %d\n", s->row_no);
  /* printf("\n"); */
}

// Assuming that the terminal or non terminal length in the grammar will not
// exceed 32 characters ever.

LinkedList *compute_first(Symbol *curr) {
  LinkedList *ll = create_linked_list();

  if (curr->is_terminal) {
    insert_node(curr, ll, true);
    return ll;
  }

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    if (strcmp(symbols[i]->name, curr->name) == 0) {
      // printf("Sending: %s", curr->right->name);
      Symbol *temp = symbols[i]->right;
      // printf("%s : ", temp->name);

      while (temp != NULL) {
        LinkedList *first = compute_first(temp);

        // print_list(first);
        merge_list(ll, first);

        if (!find_node("#", ll))
          break;

        // printf("after find node statement\n");

        if (temp->right != NULL)
          delete_node("#", ll);
        temp = temp->right;
      }
    }
  }

  return ll;
}

LinkedList *compute_follow(Symbol *curr) {
  /* printf("curr not null\n"); */
  LinkedList *ll = create_linked_list();
  if (curr == NULL)
    return ll;

  if (curr->is_terminal) {
    insert_node(curr, ll, true);
    return ll;
  }

  /* printf("Scanning: %s\n", curr->name); */

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    Symbol *temp = symbols[i]->right;
    // printf("Seg fault may be due to total symbols : %s\n", symbols[i]->name);

    while (temp != NULL) {
      if (strcmp(temp->name, curr->name) == 0) {

        // ABCD

        if (temp->right != NULL) {
          temp = temp->right;

          // printf("h3ere\n");

          while (temp != NULL) {
            // printf("before\n");
            LinkedList *first = compute_first(temp);
            // printf("finding first done\n");
            merge_list(ll, first);

            if (!find_node("#", first))
              break;

            if (temp->right != NULL)
              delete_node("#", ll);

            temp = temp->right;
          }

          if (find_node("#", ll) && strcmp(curr->name, symbols[i]->name) != 0) {
            delete_node("#", ll);
            LinkedList *follow = compute_follow(symbols[i]);
            merge_list(ll, follow);
          }

          if (temp == NULL)
            break;

        } else if (strcmp(curr->name, symbols[i]->name) != 0) {
          LinkedList *follow = compute_follow(symbols[i]);
          merge_list(ll, follow);
        } else if (strcmp(curr->name, symbols[i]->name) == 0) {
          break;
        }
      }
      temp = temp->right;
    }
  }
  return ll;
}

void build_grammar(char *grammar_file) {
  // grammar = read_file("dummy_grammar1.txt");
  grammar = read_grammar_file(grammar_file);
  //
  // printf("%d", GRAMMAR_SIZE);

  // for (int i = 0; i < GRAMMAR_SIZE; i++) {
  //   printf("%s\n", grammar[i]);
  // }

  // find symbols from this.
  Symbol *prev = NULL;
  for (int i = 0; i < GRAMMAR_SIZE; i++) {
    int j = 0;
    int sz = 0;
    int symbols_for_current_row = 0;

    char symbol_name[32] = {'@'};
    while (grammar[i][j] != '\0') {
      if (!isspace(grammar[i][j])) {
        symbol_name[sz] = grammar[i][j];
        sz++;
      } else {
        if (symbol_name[0] == '=') {
          sz = 0;
          j++;
          continue;
        }

        Symbol *new = (Symbol *)malloc(sizeof(Symbol));

        new->name = (char *)malloc(sz * sizeof(char));
        for (int k = 0; k < sz; k++)
          new->name[k] = symbol_name[k];

        // need to create the linked list first.
        new->first = create_linked_list();
        new->follow = create_linked_list();
        new->row_no = i;

        if (prev != NULL && prev->row_no == new->row_no) {
          prev->right = new;
        }

        if (isupper(symbol_name[0])){
          new->is_terminal = false;
          for(int k=0; k<N_TERMINAL_SYM; k++){
            if(strcmp(new->name, n_term_str[k]) == 0){
              new->non_terminal = k;
              new->terminal = -1;
              NT_TO_ROW[k] = i;
            }
          }
        }
        else{
          new->is_terminal = true;
          for(int k=0; k<TERMINAL_SYM; k++){
            if(strcmp(new->name, term_str[k]) == 0){
              new->terminal = k;
              new->non_terminal = -1;
            }
          }
        }

        prev = new;
        // TODO: Do dynamic memory allocation here.

        if (symbols_for_current_row == 0) {
          symbols_for_current_row++;
          symbols[TOTAL_SYMBOLS] = new;
          TOTAL_SYMBOLS++;
        }
        sz = 0;
      }
      j++;
    }
    symbols_for_current_row = 0;
  }
}

Symbol **generate_parse_table() {
  // generates the parse table required for the parsing process of the compiler.

  // array of first and follows.

    printf("he %d\n", TOTAL_SYMBOLS);
  data = (LinkedList **)malloc(TOTAL_SYMBOLS * sizeof(LinkedList *));

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
        printf("On %d\n", i);
    data[i] = create_linked_list();
    Symbol *temp = symbols[i]->right;

    while (temp != NULL) {
      LinkedList *first = compute_first(temp);
      merge_list(data[i], first);

      if (!find_node("#", data[i]))
        break;

      if (temp->right != NULL)
        delete_node("#", data[i]);
      temp = temp->right;
    }

        printf("out %d\n", i);
    if (find_node("#", data[i])) {
        delete_node("#", data[i]);
        printf("r %d\n", i);
        print_symbol_details(symbols[i], NULL);
        LinkedList *ret = compute_follow(symbols[i]);
        merge_list(data[i], ret);
        printf("mer %d\n", i);
    }
  }

  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    printf("%s: ", symbols[i]->name);
    print_list(data[i], NULL);
  }

  return NULL;
}

void print_parse_table(){

    int max_nt = 0;
    
    for(int i=0; i<N_TERMINAL_SYM; i++)
      if(strlen(n_term_str[i]) > max_nt)
        max_nt = strlen(n_term_str[i]);

    int table_length = 2 + max_nt;
    int table_height = 4 + 3*N_TERMINAL_SYM;

    for(int i=0; i<TERMINAL_SYM; i++)
      table_length += strlen(term_str[i])+3;
    
    // printf("%d %d %d\n", table_length, table_height, max_nt);
    for(int i=0; i<table_height; i++){
      
      switch(i%3){

        case 0:{
          if(i==0)
          printf(" ");
        if(i!=0)
          printf("|");

          for(int j=0; j<table_length; j++)
          printf("_");
          if(i!=0)
            printf("|");  
            printf("\n");
          break;
        }
        case 1:{

          printf("|");
          for(int j=0; j<table_length; j++)
            printf(" ");
          printf("|\n");
          break;

        }

        case 2:{

          if(i==2){
            printf("|");
            for(int j=0; j<max_nt +2; j++)
              printf(" ");
              printf("|");
              for(int j=0; j<TERMINAL_SYM; j++)
                printf(" %s |", term_str[j]);
                printf("\n");
          }

          else {
            printf("| %s", n_term_str[i/3 -1]);
            for(int j=0; j<max_nt-strlen(n_term_str[i/3 -1])+1; j++)
              printf(" ");
              printf("| ");
              for(int j=0; j<TERMINAL_SYM; j++){
                if(parser_table[i/3-1][j] != NULL)
                printf("%d", parser_table[i/3-1][j] -> row_no);
                else printf(".");
                for(int k=0; k<strlen(term_str[j]); k++)
                  printf(" ");
                  printf("| ");
              }
              printf("\n");
          }
        }
      }
    }
}

void parse_table_make(){

    parser_table = (Symbol ***) malloc(sizeof(Symbol **) * N_TERMINAL_SYM);
    for(int i=0; i<N_TERMINAL_SYM; i++)
        parser_table[i] = (Symbol **) malloc(sizeof(Symbol*) * TERMINAL_SYM);

    printf("\n \n");


    for(int i=0; i<TOTAL_SYMBOLS; i++){
        Symbol *curr = symbols[i]; // current head of grammar
        int nt = -1;
        // printf("%s\n", curr->name);

        if(!curr->is_terminal){

        for(int i=0; i<N_TERMINAL_SYM; i++)
            if(strcmp(curr->name, n_term_str[i]) == 0)
                nt = i;
        LinkedList* ls = data[i]; //getting first of the grammar

        Node *current = ls->head;
            bool isNotLL1 = false;
            while(current != NULL){
                Symbol *temp = current->symbol;
                // printf("%s ", temp->name);
                int term = -1;
                for(int j=0; j<TERMINAL_SYM; j++){

                    if(strcmp(temp->name, "#") != 0)  // if the terminal is not epsilon

                    if(strcmp(temp->name, term_str[j]) == 0){
                        term = j;
                        if(parser_table[nt][term] == NULL){
                            parser_table[nt][term] = curr; // Rule for grammar
                        }
                        else {
                            isNotLL1 = true;
                        }
                    }
                }
                current = current->next;
            }
                // print_list(ls);
                if(isNotLL1){
                  printf("GIVEN GRAMMAR IS NOT LL1 !!!!!!!\n");
                  exit(1);
                }
        }
    }
    print_parse_table();
}

/* int main() { */
/*     build_grammar(); */
/*     generate_parse_table(); */
/*     parse_table_make(); */
/*     print_symbol_details(symbols[1]->right, NULL); */
/*     return 0; */
/* } */

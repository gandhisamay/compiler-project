/*
 * Group 22
 * Samay Gandhi 2020A7PS0299P
 * Mohit Makwana 2020A7PS0048P
 * Kathan Patel 2020A7PS0058P
 * Aditya Sheth 2020A7PS1511P
 * Aryan Chavan 2020A7PS1692P
 */

#include "parse_tree.h"
#include <stdio.h>
#define HASH_SIZE 35
// #define BUFFER_SIZE 100
#define P 7
#define MAX_LEX 20

int ptr;
int start;
int state;
int line_no;
char lexeme[MAX_LEX + 5];
int to_be_scanned;
int stop = -1;
int LOOKUP_SET = 0;

int BUFFER_SIZE = 100;
char *Buffer;
/* typedef enum */
/* { */
/*     dECLARE, */
/*     $, */
/*     mODULE, */
/*     iD, */
/*     sEMICOL, */
/*     dRIVERDEF, */
/*     dRIVER, */
/*     pROGRAM, */
/*     dRIVERENDDEF, */
/*     dEF, */
/*     eNDDEF, */
/*     tAKES, */
/*     iNPUT, */
/*     sQBO, */
/*     sQBC, */
/*     rETURNS, */
/*     cOLON, */
/*     cOMMA, */
/*     iNTEGER, */
/*     rEAL, */
/*     bOOLEAN, */
/*     aRRAY, */
/*     oF, */
/*     iN, */
/*     sTART, */
/*     eND, */
/*     gET_VALUE, */
/*     bO, */
/*     bC, */
/*     pRINT, */
/*     tRUE, */
/*     fALSE, */
/*     nUM, */
/*     rNUM, */
/*     aSSIGNOP, */
/*     uSE, */
/*     wITH, */
/*     pARAMETERS, */
/*     pLUS, */
/*     mINUS, */
/*     mUL, */
/*     dIV, */
/*     aND, */
/*     oR, */
/*     lT, */
/*     lE, */
/*     gT, */
/*     gE, */
/*     eQ, */
/*     nE, */
/*     sWITCH, */
/*     cASE, */
/*     bREAK, */
/*     dEFAULT, */
/*     fOR, */
/*     wHILE, */
/*     rANGEOP, */
/*     TERMINAL_SYM, */
/*     lEX_ERROR, */
/* } terminals; */


typedef struct Error {
  int line;
  int type;
  TOKEN token;
  Symbol *stack_top;
  struct Error *next;
} Error;

typedef struct ErrorList {
  Error *head;
  Error *tail;
  int size;
} ErrorList;

ErrorList *ERROR_LIST;
char *error_msg(int error_type);
void print_error_list(ErrorList *list, FILE *debug_fp, int strict);
Error *create_new_error(int line, int type, TOKEN token, Symbol *symbol);
ErrorList *create_error_list();
void insert_error(ErrorList *list, Error *new_error);

typedef struct ele {
  char key[20];
  terminals name;
} Element;

Element *Lookup_Table[HASH_SIZE];

int hash_code(char s[]);

terminals search(char key[], Element *table[]);

void insert(char key[], terminals name, Element *table[]);

void populate_buffer(FILE *fp);
char next_char(FILE *fp);
void retract(int num);
terminals lookup(char *lexeme);
void populate_lookup();
TOKEN is_tkn(FILE *fp);
void lexer_reset(FILE *fp);
TOKEN eval_token(FILE *fp);
void remove_comments(FILE *ipt, char *opt_name);
int test_lexer_run(char *program_file);
void print_token_details(TOKEN curr, FILE *token_fp);

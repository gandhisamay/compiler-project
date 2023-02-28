#include <stdio.h>
#include "parse_tree.h"
#define HASH_SIZE 32
#define BUFFER_SIZE 100
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

char Buffer[BUFFER_SIZE];
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

typedef struct token
{
    terminals name;
    int line;
    union
    {
        char id[20];
        int num;
        /* float rnum; */
        double rnum;
    };
} TOKEN;

typedef struct ele
{
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
int test_lexer_run(char *program_file, char *tokenized_file);
void print_token_details(TOKEN curr, FILE *token_fp);

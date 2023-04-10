#include <stdio.h>
#include <stdlib.h>
typedef enum {
  PLUS,
  SUB,
  MUL,
  DIV,
  GE,
  GT,
  LE,
  LT,
  EQ,
  NE,
  AND,
  OR,
  UPLUS,
  UMINUS,
  LABEL,
  GET_VALUE,
  PRINT,
  ASSIGN,
  GOTO_UNCOND,
  IF_TRUE_GOTO,
  INP_PARAM,
  OUTP_PARAM,
  // for function call.
  ACTUAL_PARAM,
  RETURN_PARAM,
  FUNC_CALL,
  INDEXED_COPY,
  ARRAY_ACCESS,
  DECLARE_DYN_ARR,
  DECLARE_STATIC_ARR,
  RETURN,
  FN_DEFN,
  EXIT_PROGRAM_IF_TRUE
} label;

const char *LABEL_TO_STR[] = {"PLUS",
                              "SUB",
                              "MUL",
                              "DIV",
                              "GE",
                              "GT",
                              "LE",
                              "LT",
                              "EQ",
                              "NE",
                              "AND",
                              "OR",
                              "UPLUS",
                              "UMINUS",
                              "LABEL",
                              "GET_VALUE",
                              "PRINT",
                              "ASSIGN",
                              "GOTO_UNCOND",
                              "IF_TRUE_GOTO",
                              "INP_PARAM",
                              "OUTP_PARAM",
                              "ACTUAL_PARAM",
                              "RETURN_PARAM",
                              "FUNC_CALL",
                              "INDEXED_COPY",
                              "ARRAY_ACCESS",
                              "DECLARE_DYN_ARR",
                              "DECLARE_STATIC_ARR",
                              "RETURN",
                              "FN_DEFN",
                              "EXIT_PROGRAM_IF_TRUE"};
//
typedef struct QuadNode {
  label op;
  char *arg1;
  char *arg2;
  char *result;
  struct QuadNode *next;
} QuadNode;

typedef struct {
  QuadNode *head;
  QuadNode *tail;
  int size;
} Quadruple;

void print_quadlist(Quadruple *ll, FILE *debug_fp);
QuadNode *create_new_quad_node();
Quadruple *create_quadlist();
void insert_quadnode(QuadNode *temp, Quadruple *ll);

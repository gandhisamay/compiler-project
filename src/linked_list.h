/*
 * Group 22
 * Samay Gandhi 2020A7PS0299P
 * Mohit Makwana 2020A7PS0048P
 * Kathan Patel 2020A7PS0058P
 * Aditya Sheth 2020A7PS1511P
 * Aryan Chavan 2020A7PS1692P
 */

#include "stdbool.h"
#include <stdio.h>

/* typedef enum
 * {dECLARE,$,mODULE,iD,iN,sEMICOL,dRIVERDEF,dRIVER,pROGRAM,dRIVERENDDEF,dEF,eNDDEF,tAKES,iNPUT,sQBO,sQBC,rETURNS,cOLON,cOMMA,iNTEGER,rEAL,bOOLEAN,aRRAY,oF,sTART,eND,gET_VALUE,bO,bC,pRINT,tRUE,fALSE,nUM,rNUM,aSSIGNOP,uSE,wITH,pARAMETERS,
 */
/* pLUS,mINUS,mUL,dIV,aND,oR,lT,lE,gT,gE,eQ,nE,sWITCH,cASE,bREAK,dEFAULT,fOR,wHILE,rANGEOP,
 * TERMINAL_SYM, lEX_ERROR}terminals; */

/* char *term_str[] = {"dECLARE","$","mODULE","iD",
 * "iN","sEMICOL","dRIVERDEF","dRIVER","pROGRAM","dRIVERENDDEF","dEF","eNDDEF","tAKES","iNPUT","sQBO","sQBC","rETURNS","cOLON","cOMMA","iNTEGER","rEAL","bOOLEAN","aRRAY","oF","sTART","eND","gET_VALUE",
 */
/* "bO","bC","pRINT","tRUE","fALSE","nUM","rNUM","aSSIGNOP","uSE","wITH","pARAMETERS","
 * pLUS","mINUS","mUL","dIV","aND","oR","lT","lE","gT","gE","eQ","nE","sWITCH","cASE","bREAK","dEFAULT","fOR","wHILE","rANGEOP"};
 */

/* typedef enum { */
/* dECLARE,$,mODULE,iD,sEMICOL,dRIVERDEF,dRIVER,pROGRAM,dRIVERENDDEF,dEF,eNDDEF,tAKES,iNPUT,sQBO,sQBC,rETURNS,cOLON,cOMMA,iNTEGER,rEAL,bOOLEAN,aRRAY,oF,rANGEOP,sTART,eND,gET_VALUE,bO,bC,pRINT,nUM,rNUM,tRUE,fALSE,aSSIGNOP,pLUS,mINUS,uSE,wITH,pARAMETERS,mUL,dIV,aND,oR,lT,lE,gT,gE,eQ,nE,sWITCH,cASE,bREAK,dEFAULT,fOR,iN,wHILE,TERMINAL_SYM,
 * lEX_ERROR} terminals; */

typedef enum {
  dECLARE,
  $,
  mODULE,
  iD,
  sEMICOL,
  dRIVERDEF,
  dRIVER,
  pROGRAM,
  dRIVERENDDEF,
  dEF,
  eNDDEF,
  tAKES,
  iNPUT,
  sQBO,
  sQBC,
  rETURNS,
  cOLON,
  cOMMA,
  iNTEGER,
  rEAL,
  bOOLEAN,
  aRRAY,
  oF,
  rANGEOP,
  sTART,
  eND,
  gET_VALUE,
  bO,
  bC,
  pRINT,
  tRUE,
  fALSE,
  nUM,
  rNUM,
  aSSIGNOP,
  pLUS,
  mINUS,
  uSE,
  wITH,
  pARAMETERS,
  mUL,
  dIV,
  aND,
  oR,
  lT,
  lE,
  gT,
  gE,
  eQ,
  nE,
  sWITCH,
  cASE,
  bREAK,
  dEFAULT,
  fOR,
  iN,
  wHILE,
  TERMINAL_SYM,
  lEX_ERROR
} terminals;

char *term_str[] = {
    "dECLARE",   "$",         "mODULE",       "iD",           "sEMICOL",
    "dRIVERDEF", "dRIVER",    "pROGRAM",      "dRIVERENDDEF", "dEF",
    "eNDDEF",    "tAKES",     "iNPUT",        "sQBO",         "sQBC",
    "rETURNS",   "cOLON",     "cOMMA",        "iNTEGER",      "rEAL",
    "bOOLEAN",   "aRRAY",     "oF",           "rANGEOP",      "sTART",
    "eND",       "gET_VALUE", "bO",           "bC",           "pRINT",
    "tRUE",      "fALSE",     "nUM",          "rNUM",         "aSSIGNOP",
    "pLUS",      "mINUS",     "uSE",          "wITH",         "pARAMETERS",
    "mUL",       "dIV",       "aND",          "oR",           "lT",
    "lE",        "gT",        "gE",           "eQ",           "nE",
    "sWITCH",    "cASE",      "bREAK",        "dEFAULT",      "fOR",
    "iN",        "wHILE",     "TERMINAL_SYM", "lEX_ERROR"};

/* char *term_str[] = {"dECLARE", "$", "mODULE", "iD", "sEMICOL", "dRIVERDEF",
 * "dRIVER", "pROGRAM", "dRIVERENDDEF", "dEF", "eNDDEF", "tAKES", "iNPUT",
 * "sQBO", "sQBC", "rETURNS", "cOLON", "cOMMA", "iNTEGER", "rEAL", "bOOLEAN",
 * "aRRAY", "oF", "rANGEOP", "sTART", "eND", "gET_VALUE", "bO", "bC", "pRINT",
 * "nUM", "rNUM", "tRUE", "fALSE", "aSSIGNOP", "pLUS", "mINUS", "uSE", "wITH",
 * "pARAMETERS", "mUL", "dIV", "aND", "oR", "lT", "lE", "gT", "gE", "eQ", "nE",
 * "sWITCH", "cASE", "bREAK", "dEFAULT", "fOR", "iN", "wHILE", "TERMINAL_SYM",
 * "lEX_ERROR"}; */

/* typedef enum
 * {S,Program,ModuleDeclarations,ModuleDeclaration,OtherModules,DriverModule,Module,Ret,Input_plist,Inpl_1,Output_plist,Onpl_1,DataType,Type,ModuleDef,Statements,Statement,IoStmt,Var,BoolConstt,Var_id_num,WhichId,SimpleStmt,AssignmentStmt,WhichStmt,LvalueiDStmt,LvalueARRStmt,Index,ModuleReuseStmt,Optional,IdList,Idl_1,Expression,U,New_NT,Unary_op,ArithmeticOrBooleanExpr,ArxBool_1,AnyTerm,AnyTerm_1,ArithmeticExpr,Arx_1,Term,Term_1,Factor,Op1,Op2,LogicalOp,RelationalOp,DeclareStmt,ConditionalStmt,CaseStmts,
 * CaseStmt,Value,Default,IterativeStmt,Range,Range_Index,Range_Array,Array_Index,
 * N_TERMINAL_SYM} n_terminals; */

/* char *n_term_str[] =
 * {"S","Program","ModuleDeclarations","ModuleDeclaration","OtherModules","DriverModule","Module","Ret","Input_plist","Inpl_1","Output_plist","Onpl_1","DataType","Type","ModuleDef","Statements","Statement","IoStmt","Var","BoolConstt","Var_id_num","WhichId",
 */
/* "SimpleStmt","AssignmentStmt","WhichStmt","LvalueiDStmt","LvalueARRStmt","Index","ModuleReuseStmt","Optional","IdList","Idl_1","Expression","U","New_NT","Unary_op","ArithmeticOrBooleanExpr","ArxBool_1","AnyTerm","AnyTerm_1","ArithmeticExpr","Arx_1","Term","Term_1","Factor","Op1","Op2","LogicalOp","RelationalOp","DeclareStmt",
 */
/* "ConditionalStmt","CaseStmts","CaseStmt","Value","Default","IterativeStmt","Range","Range_Index","Range_Array","Array_Index"};
 */

/* typedef enum { */
/* S,Program,ModuleDeclarations,ModuleDeclaration,OtherModules,DriverModule,Module,Ret,Input_plist,Inpl_1,Output_plist,Onpl_1,DataType,Range_Array,Type,ModuleDef,Statements,Statement,IoStmt,Var_id_num,Array_element_for_print,Var_print,Arr_value,BoolConstt,SimpleStmt,AssignmentStmt,WhichStmt,LvalueiDStmt,LvalueARRStmt,Array_Index,New_index,Sign,ModuleReuseStmt,Actual_para_list,Optional,IdList,Idl_1,Expression,U,New_NT,Unary_op,ArithmeticOrBooleanExpr,N7,AnyTerm,N8,ArithmeticExpr,N4,Term,N5,Factor,N11,Element_index_with_expressions,ArrExpr,Arr_N4,ArrTerm,Arr_N5,ArrFactor,Op1,Op2,LogicalOp,RelationalOp,DeclareStmt,ConditionalStmt,CaseStmts,N9,Value,Default,IterativeStmt,Range,Range_for_loop,Index_for_loop,New_index_for_loop,Sign_for_loop,Range_Index,N_TERMINAL_SYM}
 * n_terminals; */

typedef enum {
  S,
  Program,
  ModuleDeclarations,
  ModuleDeclaration,
  OtherModules,
  DriverModule,
  Module,
  Ret,
  Input_plist,
  N1,
  Output_plist,
  N2,
  DataType,
  Range_arrays,
  Type,
  ModuleDef,
  Statements,
  Statement,
  IoStmt,
  BoolConstt,
  Id_num_rnum,
  Var_id_num,
  Array_element_for_print,
  Var_print,
  P1,
  SimpleStmt,
  AssignmentStmt,
  WhichStmt,
  LvalueIDStmt,
  LvalueARRStmt,
  Index_arr,
  New_index,
  Sign,
  ModuleReuseStmt,
  Actual_para_list,
  Optional,
  IdList,
  N3,
  Expression,
  U,
  New_NT,
  Unary_op,
  ArithmeticOrBooleanExpr,
  N7,
  AnyTerm,
  N8,
  ArithmeticExpr,
  N4,
  Term,
  N5,
  Factor,
  N11,
  Element_index_with_expressions,
  N10,
  ArrExpr,
  Arr_N4,
  ArrTerm,
  Arr_N5,
  ArrFactor,
  Op1,
  Op2,
  LogicalOp,
  RelationalOp,
  DeclareStmt,
  ConditionalStmt,
  CaseStmts,
  N9,
  Value,
  Default,
  IterativeStmt,
  Range,
  Range_for_loop,
  Index_for_loop,
  New_index_for_loop,
  Sign_for_loop,
  Actual_para_list1,
  Actual_para_iD,
  N_TERMINAL_SYM
} n_terminals;

char *n_term_str[] = {"S",
                      "Program",
                      "ModuleDeclarations",
                      "ModuleDeclaration",
                      "OtherModules",
                      "DriverModule",
                      "Module",
                      "Ret",
                      "Input_plist",
                      "N1",
                      "Output_plist",
                      "N2",
                      "DataType",
                      "Range_arrays",
                      "Type",
                      "ModuleDef",
                      "Statements",
                      "Statement",
                      "IoStmt",
                      "BoolConstt",
                      "Id_num_rnum",
                      "Var_id_num",
                      "Array_element_for_print",
                      "Var_print",
                      "P1",
                      "SimpleStmt",
                      "AssignmentStmt",
                      "WhichStmt",
                      "LvalueIDStmt",
                      "LvalueARRStmt",
                      "Index_arr",
                      "New_index",
                      "Sign",
                      "ModuleReuseStmt",
                      "Actual_para_list",
                      "Optional",
                      "IdList",
                      "N3",
                      "Expression",
                      "U",
                      "New_NT",
                      "Unary_op",
                      "ArithmeticOrBooleanExpr",
                      "N7",
                      "AnyTerm",
                      "N8",
                      "ArithmeticExpr",
                      "N4",
                      "Term",
                      "N5",
                      "Factor",
                      "N11",
                      "Element_index_with_expressions",
                      "N10",
                      "ArrExpr",
                      "Arr_N4",
                      "ArrTerm",
                      "Arr_N5",
                      "ArrFactor",
                      "Op1",
                      "Op2",
                      "LogicalOp",
                      "RelationalOp",
                      "DeclareStmt",
                      "ConditionalStmt",
                      "CaseStmts",
                      "N9",
                      "Value",
                      "Default",
                      "IterativeStmt",
                      "Range",
                      "Range_for_loop",
                      "Index_for_loop",
                      "New_index_for_loop",
                      "Sign_for_loop",
                      "Actual_para_list1",
                      "Actual_para_iD",
                      "N_TERMINAL_SYM"};

int NT_TO_ROW[N_TERMINAL_SYM];

/* char *n_term_str[] =
 * {"S","Program","ModuleDeclarations","ModuleDeclaration","OtherModules","DriverModule","Module","Ret","Input_plist","Inpl_1","Output_plist","Onpl_1","DataType","Range_Array","Type","ModuleDef","Statements","Statement","IoStmt","Var_id_num","Array_element_for_print","Var_print","Arr_value","BoolConstt","SimpleStmt","AssignmentStmt","WhichStmt","LvalueiDStmt","LvalueARRStmt","Array_Index","New_index","Sign","ModuleReuseStmt","Actual_para_list","Optional","IdList","Idl_1","Expression","U","New_NT","Unary_op","ArithmeticOrBooleanExpr","N7","AnyTerm","N8","ArithmeticExpr","N4","Term","N5","Factor","N11","Element_index_with_expressions","ArrExpr","Arr_N4","ArrTerm","Arr_N5","ArrFactor","Op1","Op2","LogicalOp","RelationalOp","DeclareStmt","ConditionalStmt","CaseStmts","N9","Value","Default","IterativeStmt","Range","Range_for_loop","Index_for_loop","New_index_for_loop","Sign_for_loop","Range_Index","N_TERMINAL_SYM"};
 */

typedef struct token {
  terminals name;
  int line;
  union {
    char id[20];
    int num;
    /* float rnum; */
    double rnum;
  };
} TOKEN;

typedef struct Symbol {
  char *name;
  bool is_terminal;
  terminals terminal;
  n_terminals non_terminal;
  int row_no;

  struct LinkedList *first;
  struct LinkedList *follow;

  struct Symbol *right;
  // struct Symbol *bottom;

} Symbol;

struct Node {
  struct Node *next;
  Symbol *symbol;
};

typedef struct Node Node;

struct LinkedList {
  Node *head;
  Node *tail;
  int size;
};

typedef struct LinkedList LinkedList;

Node *create_new_node(Symbol *symbol);
LinkedList *create_linked_list();
void insert_node(Symbol *symbol, LinkedList *ll, bool check_if_present);
void print_list(LinkedList *ll, FILE *debug_fp);
void merge_list(LinkedList *l1, LinkedList *l2);
bool find_node(char *name, LinkedList *ll);
void delete_node(char *name, LinkedList *ll);
int get_length(Symbol *Rule);

// Debugging use cases
#define PRINT_RED "\x1b[31m"
#define PRINT_GREEN "\x1b[32m"
#define PRINT_YELLOW "\x1b[33m"
#define PRINT_BLUE "\x1b[34m"
#define PRINT_MAGENTA "\x1b[35m"
#define PRINT_CYAN "\x1b[36m"
#define PRINT_RESET "\x1b[0m"

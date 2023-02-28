#include "linked_list.c"
#include "stdbool.h"

typedef struct TreeNode{
    struct TreeNode* parent;
    struct TreeNode* head;
    struct TreeNode* tail;
    struct TreeNode* sibling;
    struct Symbol *symbol;
} TreeNode;

int GRAMMAR_SIZE = 0;
int RULE_WIDTH = 512;
int TOTAL_SYMBOLS = 0;
int MAX_SYMBOLS_ARRAY_SIZE = 64;
char **grammar;
Symbol *symbols[256];
LinkedList **data;
Symbol*** parser_table;

typedef enum {dECLARE,$,mODULE,iD,iN,sEMICOL,dRIVERDEF,dRIVER,pROGRAM,dRIVERENDDEF,dEF,eNDDEF,tAKES,iNPUT,sQBO,sQBC,rETURNS,cOLON,cOMMA,iNTEGER,rEAL,bOOLEAN,aRRAY,oF,sTART,eND,gET_VALUE,bO,bC,pRINT,tRUE,fALSE,nUM,rNUM,aSSIGNOP,uSE,wITH,pARAMETERS,
pLUS,mINUS,mUL,dIV,aND,oR,lT,lE,gT,gE,eQ,nE,sWITCH,cASE,bREAK,dEFAULT,fOR,wHILE,rANGEOP, TERMINAL_SYM, lEX_ERROR}terminals;

char *term_str[] = {"$","dECLARE","mODULE","iD","sEMICOL","dRIVERDEF","dRIVER","pROGRAM","dRIVERENDDEF","dEF","eNDDEF","tAKES","iNPUT","sQBO","sQBC","rETURNS","cOLON","cOMMA","iNTEGER","rEAL","bOOLEAN","aRRAY","oF","sTART","eND","gET_VALUE",
"bO","bC","pRINT","tRUE","fALSE","nUM","rNUM","aSSIGNOP","uSE","wITH","pARAMETERS"," pLUS","mINUS","mUL","dIV","aND","oR","lT","lE","gT","gE","eQ","nE","sWITCH","cASE","bREAK","dEFAULT","fOR","wHILE","rANGEOP"};


typedef enum {S,Program,ModuleDeclarations,ModuleDeclaration,OtherModules,DriverModule,Module,Ret,Input_plist,Inpl_1,Output_plist,Onpl_1,DataType,Type,ModuleDef,Statements,Statement,IoStmt,Var,BoolConstt,Var_id_num,WhichId,SimpleStmt,AssignmentStmt,WhichStmt,LvalueiDStmt,LvalueARRStmt,Index,ModuleReuseStmt,Optional,IdList,Idl_1,Expression,U,New_NT,Unary_op,ArithmeticOrBooleanExpr,ArxBool_1,AnyTerm,AnyTerm_1,ArithmeticExpr,Arx_1,Term,Term_1,Factor,Op1,Op2,LogicalOp,RelationalOp,DeclareStmt,ConditionalStmt,CaseStmts, CaseStmt,Value,Default,IterativeStmt,Range,Range_Index,Range_Array,Array_Index, N_TERMINAL_SYM}n_terminals;

char *n_term_str[] = {"S","Program","ModuleDeclarations","ModuleDeclaration","OtherModules","DriverModule","Module","Ret","Input_plist","Inpl_1","Output_plist","Onpl_1","DataType","Type","ModuleDef","Statements","Statement","IoStmt","Var","BoolConstt","Var_id_num","WhichId",
"SimpleStmt","AssignmentStmt","WhichStmt","LvalueiDStmt","LvalueARRStmt","Index","ModuleReuseStmt","Optional","IdList","Idl_1","Expression","U","New_NT","Unary_op","ArithmeticOrBooleanExpr","ArxBool_1","AnyTerm","AnyTerm_1","ArithmeticExpr","Arx_1","Term","Term_1","Factor","Op1","Op2","LogicalOp","RelationalOp","DeclareStmt",
"ConditionalStmt","CaseStmts","CaseStmt","Value","Default","IterativeStmt","Range","Range_Index","Range_Array","Array_Index"};

TreeNode* ParseTree;

char **read_grammar_file(char *file); 
void build_grammar();
TreeNode* create_parse_tree();
TreeNode* create_treeNode();
TreeNode* insert_child(TreeNode* parent, Symbol *symbol); // pointer to parent, and LHS of grammar
void print_terminal_list();
/* typedef struct LinkedList LinkedList; */

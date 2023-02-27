#define HASH_SIZE 32
#define BUFFER_SIZE 30
#define P 7
#define MAX_LEX 20


int ptr;
int start;
int state;
int line_no;
char lexeme[MAX_LEX+5];
int to_be_scanned;
int stop = -1;
int LOOKUP_SET = 0;

char Buffer[BUFFER_SIZE];
typedef enum{
    LEX_ERROR, DOLLAR, INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TAKES, INPUT, RETURNS, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE, ID, NUM, RNUM, AND, OR, TRUE, FALSE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, DRIVERDEF, DRIVERENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, COMMENTMARK
} tokens;

typedef struct token {
    tokens name;
    int line;
    union {
        char id[20];
        int num;
        /* float rnum; */
        double rnum;
    };
} TOKEN;

typedef struct ele {   
    char key[20];
    tokens name;
} Element;


Element *Lookup_Table[HASH_SIZE];


int hash_code(char s[]);

tokens search(char key[], Element *table[]);

void insert(char key[], tokens name, Element *table[]);

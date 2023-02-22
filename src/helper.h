

int state;

int ptr;
int start;

int line_no;

char buffer[20];

typedef enum{
    LEX_ERROR, DOLLAR, INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TAKES, INPUT, RETURNS, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE, ID, NUM, RNUM, AND, OR, TRUE, FALSE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, DRIVERDEF, DRIVERENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, COMMENTMARK
}tokens;

typedef struct token
{
    tokens name;
    int line;
    union 
    {
        char id[20];
        int num;
        /* float rnum; */
        double rnum;
    };
}TOKEN;



#define HASH_SIZE 32
#define BUFFER_SIZE 30
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
typedef enum
{
    $,
    dECLARE,
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
    iN,
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
    uSE,
    wITH,
    pARAMETERS,
    pLUS,
    mINUS,
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
    wHILE,
    rANGEOP,
    TERMINAL_SYM,
    lEX_ERROR,
} tokens;

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
} TOKEN;

typedef struct ele
{
    char key[20];
    tokens name;
} Element;

Element *Lookup_Table[HASH_SIZE];

int hash_code(char s[]);

tokens search(char key[], Element *table[]);

void insert(char key[], tokens name, Element *table[]);

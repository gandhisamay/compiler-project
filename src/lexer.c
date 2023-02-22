#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexer_helper.h"

void retract(int num,FILE* fp )
{
    ptr -= num;
    fseek(fp,-num,SEEK_CUR);
}

tokens lookup(char *lexeme)
{   
    tokens result = search(lexeme, Lookup_Table);
    return result;
    /* if( result == NULL) { */
    /*     return ID; */
    /* } */
    /* else { */
    /*     return result; */
    /* } */

}

void populate_lookup(){
    insert("integer", INTEGER, Lookup_Table);
    insert("real", REAL, Lookup_Table);
    insert("boolean", BOOLEAN, Lookup_Table);
    insert("of", OF, Lookup_Table);
    insert("array", ARRAY, Lookup_Table);
    insert("start", START, Lookup_Table);
    insert("end", END, Lookup_Table);
    insert("declare", DECLARE, Lookup_Table);
    insert("module", MODULE, Lookup_Table);
    insert("driver", DRIVER, Lookup_Table);
    insert("program", PROGRAM, Lookup_Table);
    insert("get_value", GET_VALUE, Lookup_Table);
    insert("print", PRINT, Lookup_Table);
    insert("use", USE, Lookup_Table);
    insert("with", WITH, Lookup_Table);
    insert("parameters", PARAMETERS, Lookup_Table);
    insert("takes", TAKES, Lookup_Table);
    insert("input", INPUT, Lookup_Table);
    insert("returns", RETURNS, Lookup_Table);
    insert("for", FOR, Lookup_Table);
    insert("in", IN, Lookup_Table);
    insert("switch", SWITCH, Lookup_Table);
    insert("case", CASE, Lookup_Table);
    insert("break", BREAK, Lookup_Table);
    insert("default", DEFAULT, Lookup_Table);
    insert("while", WHILE, Lookup_Table);
}

TOKEN is_tkn(FILE *fp)
{
    TOKEN tkn;
    tkn.line = line_no;
    int lex_size = ptr - start;

    if (lex_size > 20)
    {
        tkn.name = LEX_ERROR;
        return tkn;
    }
    fseek(fp, -lex_size, SEEK_CUR);
    fread(buffer, lex_size + 1, 1, fp);
    printf("\n ptr %d start %d lex_size %d\nbuffer %s \n",ptr, start, lex_size, buffer);
    switch(state){
        case 2:
            tkn.name = lookup(buffer);
            strncpy(tkn.id,buffer,lex_size);
            tkn.id[lex_size] = '\0';
            printf("\n buf %s tkn %s \n", buffer, tkn.id);
            break;
        
        case 4:
            tkn.name = NUM;
            tkn.num = atoi(buffer);
            break;
        
        case 7:
            tkn.name = RNUM;
            tkn.rnum = atof(buffer);
            break;

        case 11:
            tkn.name = RNUM;
            tkn.rnum = atof(buffer);
            break;

        case 12:
            tkn.name = NUM;
            tkn.num = atoi(buffer);
            break;
    }
    return tkn;
}

void lexer_reset()
{
    state = 0;
    line_no = 0;
    ptr = 0;
    start = 0;
}

TOKEN eval_token(FILE *fp)
{
    char c;
    TOKEN tkn;

    while (true)
    {
        tkn.line = line_no;
        switch (state)
        {
        case 0:
            c = getc(fp);
            printf("new char ptr %d %c \n", ptr, c);
            ptr++;
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
            {
                state = 1;
            }
            else if (c >= '0' && c <= '9')
            {
                state = 3;
            }
            else if (c == ' ' || c == '\t' || c == '\n')
            {
                if (c == '\n')
                    line_no++;
                state = 13;
            }
            else if (c == '+')
            {
                state = 15;
            }
            else if (c == '-')
            {
                state = 16;
            }
            else if (c == '*')
            {
                state = 17;
            }
            else if (c == '/')
            {
                state = 22;
            }
            else if (c == '<')
            {
                state = 23;
            }
            else if (c == '>')
            {
                state = 29;
            }
            else if (c == '=')
            {
                state = 35;
            }
            else if (c == '!')
            {
                state = 37;
            }
            else if (c == ':')
            {
                state = 39;
            }
            else if (c == '.')
            {
                state = 42;
            }
            else if (c == ';')
            {
                state = 44;
            }
            else if (c == ',')
            {
                state = 45;
            }
            else if (c == '[')
            {
                state = 46;
            }
            else if (c == ']')
            {
                state = 47;
            }
            else if (c == '(')
            {
                state = 48;
            }
            else if (c == ')')
            {
                state = 49;
            }
            else if (c == EOF)
            {
                tkn.name = DOLLAR;
                return tkn;
            }
            else
            {
                state = 50;
            }

            break;

        case 1:
            c = getc(fp);
            ptr++;
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9'))
            {
                state = 1;
            }
            else
            {
                state = 2;
            }
            break;

        case 2:
            retract(1,fp);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 3:
            c = getc(fp);
            ptr++;
            if (c >= '0' && c <= '9')
            {
                state = 3;
            }
            else if (c == '.')
            {
                state = 5;
            }
            else
            {
                state = 4;
            }
            break;

        case 4:
            retract(1,fp);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 5:
            c = getc(fp);
            ptr++;
            if (c == '.')
            {
                state = 12;
            }
            else if (c >= '0' && c <= '9')
            {
                state = 6;
            }
            else
            {
                state = 50;
            }
            break;

        case 6:
            c = getc(fp);
            ptr++;
            if (c >= '0' && c <= '9')
            {
                state = 6;
            }
            else if (c == 'e' || c == 'E')
            {
                state = 8;
            }
            else
            {
                state = 7;
            }
            break;

        case 7:
            retract(1,fp);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 8:
            c = getc(fp);
            ptr++;
            if (c >= '0' && c <= '9')
            {
                state = 10;
            }
            else if (c == '+' || c == '-')
            {
                state = 9;
            }
            else
            {
                state = 50;
            }
            break;

        case 9:
            c = getc(fp);
            ptr++;
            if (c >= '0' && c <= '9')
            {
                state = 10;
            }
            else
            {
                state = 50;
            }
            break;

        case 10:
            c = getc(fp);
            ptr++;
            if (c >= '0' && c <= '9')
            {
                state = 10;
            }
            else
            {
                state = 11;
            }
            break;

        case 11:
            retract(1,fp);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 12:
            retract(2,fp);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 13:
            if (c == ' ' || c == '\t' || c == '\n')
            {
                state = 13;
                if(c == '\n') line_no++;
            }
            else
            {
                state = 14;
            }
            break;

        case 14:
            retract(1,fp);
            start = ptr;
            state = 0;

            break;

        case 15:
            tkn.name  = PLUS;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"+",20);
            return tkn;
            break;

        case 16:
            tkn.name = MINUS;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"-",20);
            return tkn;
            break;

        case 17:
            c = getc(fp);
            ptr++;
            if (c == '*')
            {
                state = 19;
            }
            else
            {
                state = 18;
            }
            break;

        case 18:
            retract(1,fp);
            tkn.name = MUL;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"*",20);
            return tkn;
            break;

        case 19:
            c = getc(fp);
            ptr++;
            if (c == '*')
            {
                state = 20;
            }
            else
            {
                state = 19;
            }
            break;

        case 20:
            c = getc(fp);
            ptr++;
            if (c == '*')
            {
                state = 21;
            }
            else
            {
                state = 19;
            }
            break;

        case 21:

            state = 0;
            start = ptr;
            break;

        case 22:
            tkn.name = DIV;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"/",20);
            return tkn;
            break;

        case 23:
            c = getc(fp);
            ptr++;
            if (c == '=')
            {
                state = 25;
            }
            else if (c == '<')
            {
                state = 26;
            }
            else
            {
                state = 24;
            }
            break;

        case 24:
            retract(1,fp);
            tkn.name = LT;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"<",20);
            return tkn;
            break;

        case 25:
            tkn.name = LE;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"<=",20);
            return tkn;
            break;

        case 26:
            c = getc(fp);
            ptr++;
            if (c == '<')
            {
                state = 28;
            }
            else
            {
                state = 27;
            }
            break;

        case 27:
            retract(1,fp);
            tkn.name = DEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"<<",20);
            return tkn;
            break;

        case 28:
            tkn.name = DRIVERDEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"<<<",20);
            return tkn;
            break;

        case 29:
            c = getc(fp);
            ptr++;
            if (c == '=')
            {
                state = 31;
            }
            else if (c == '>')
            {
                state = 32;
            }
            else
            {
                state = 30;
            }
            break;

        case 30:
            retract(1,fp);
            tkn.name = GT;
            start = ptr;
            state = 0;
            strncpy(tkn.id,">",20);
            return tkn;
            break;

        case 31:
            tkn.name = GE;
            start = ptr;
            state = 0;
            strncpy(tkn.id,">=",20);
            return tkn;
            break;

        case 32:
            c = getc(fp);
            ptr++;
            if (c == '>')
            {
                state = 34;
            }
            else
            {
                state = 33;
            }
            break;

        case 33:
            retract(1,fp);
            tkn.name = ENDDEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id,">>",20);
            return tkn;
            break;

        case 34:
            tkn.name = DRIVERENDDEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id,">>>",20);
            return tkn;
            break;

        case 35:
            c = getc(fp);
            ptr++;
            if (c == '=')
            {
                state = 36;
            }
            else
            {
                state = 50;
            }
            break;

        case 36:
            tkn.name = EQ;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"==",20);
            return tkn;
            break;

        case 37:
            c = getc(fp);
            ptr++;
            if (c == '=')
            {
                state = 38;
            }
            else
            {
                state = 50;
            }
            break;

        case 38:
            tkn.name = NE;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"!=",20);
            return tkn;
            break;

        case 39:
            c = getc(fp);
            ptr++;
            if (c == '=')
            {
                state = 40;
            }
            else
            {
                state = 41;
            }
            break;

        case 40:
            tkn.name = ASSIGNOP;
            start = ptr;
            state = 0;
            strncpy(tkn.id,":=",20);
            return tkn;
            break;

        case 41:
            retract(1,fp);
            tkn.name = COLON;
            start = ptr;
            state = 0;
            strncpy(tkn.id,":",20);
            return tkn;
            break;

        case 42:
            c = getc(fp);
            ptr++;
            if (c == '.')
            {
                state = 43;
            }
            else
            {
                state = 50;
            }
            break;

        case 43:
            tkn.name = RANGEOP;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"..",20);
            return tkn;
            break;

        case 44:
            tkn.name = SEMICOL;
            printf("semicol ptr %d start %d \n", ptr, start);
            start = ptr;
            state = 0;
            strncpy(tkn.id,";",20);
            return tkn;
            break;

        case 45:
            tkn.name = COMMA;
            start = ptr;
            state = 0;
            strncpy(tkn.id,",",20);
            return tkn;
            break;

        case 46:
            tkn.name = SQBO;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"[",20);
            return tkn;
            break;

        case 47:
            tkn.name = SQBC;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"]",20);
            return tkn;
            break;

        case 48:
            tkn.name = BO;
            start = ptr;
            state = 0;
            strncpy(tkn.id,"(",20);
            return tkn;
            break;

        case 49:
            tkn.name = BC;
            start = ptr;
            state = 0;
            strncpy(tkn.id,")",20);
            return tkn;
            break;

        case 50:
            tkn.name = LEX_ERROR;
            break;

        default:
            break;
        }
    }
}

int main(int argc, char *argv[]){
    printf("Hey there %d %s %s \n", argc, argv[0], argv[1]);
    /* FILE *f = fopen(argv[1], "r"); */
    lexer_reset();
    FILE *f = fopen("test_lexer_1.txt", "r");
    /* char c = getc(f); */
    /* while(c != ';'){ */
    /*     printf("new char %c \n", c); */
    /*     c = getc(f); */
    /* } */
    TOKEN curr = eval_token(f);
    while(curr.name != DOLLAR){
        curr = eval_token(f);
        printf("token %d id %s \n", curr.line, curr.id);
    }
}

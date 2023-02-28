#include "hash_Table.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populate_buffer(FILE *fp)
{
    if (ptr == BUFFER_SIZE)
    {
        ptr = 0;
    }
    int check = fread(&Buffer[ptr], 1, (BUFFER_SIZE / 2), fp);
    to_be_scanned += check;
    if (check != (BUFFER_SIZE / 2))
    {
        Buffer[check + ptr] = '$';
        stop = check + ptr;
    }
}

char next_char(FILE *fp)
{
    if (to_be_scanned == 0)
    {
        if (ptr == BUFFER_SIZE || ptr == BUFFER_SIZE / 2)
            populate_buffer(fp);
    }
    int curr_lex_size = ptr - start;
    if (curr_lex_size < 0)
        curr_lex_size += BUFFER_SIZE;

    if (curr_lex_size < MAX_LEX)
        lexeme[curr_lex_size] = Buffer[ptr];
    ptr++;
    to_be_scanned--;
    return Buffer[ptr - 1];
}

void retract(int num)
{
    ptr -= num;
    to_be_scanned += num;
    if (ptr < 0)
        ptr += BUFFER_SIZE;
}

terminals lookup(char *lexeme)
{
    terminals result = search(lexeme, Lookup_Table);
    return result;
}

void populate_lookup()
{
    insert("integer", iNTEGER, Lookup_Table);
    insert("real", rEAL, Lookup_Table);
    insert("boolean", bOOLEAN, Lookup_Table);
    insert("of", oF, Lookup_Table);
    insert("array", aRRAY, Lookup_Table);
    insert("start", sTART, Lookup_Table);
    insert("end", eND, Lookup_Table);
    insert("declare", dECLARE, Lookup_Table);
    insert("module", mODULE, Lookup_Table);
    insert("driver", dRIVER, Lookup_Table);
    insert("program", pROGRAM, Lookup_Table);
    insert("get_value", gET_VALUE, Lookup_Table);
    insert("print", pRINT, Lookup_Table);
    insert("use", uSE, Lookup_Table);
    insert("with", wITH, Lookup_Table);
    insert("parameters", pARAMETERS, Lookup_Table);
    insert("takes", tAKES, Lookup_Table);
    insert("input", iNPUT, Lookup_Table);
    insert("returns", rETURNS, Lookup_Table);
    insert("for", fOR, Lookup_Table);
    insert("in", iN, Lookup_Table);
    insert("switch", sWITCH, Lookup_Table);
    insert("case", cASE, Lookup_Table);
    insert("break", bREAK, Lookup_Table);
    insert("default", dEFAULT, Lookup_Table);
    insert("while", wHILE, Lookup_Table);
}

TOKEN is_tkn(FILE *fp)
{
    TOKEN tkn;
    tkn.line = line_no;
    if (start == BUFFER_SIZE)
        start = 0;
    int lex_size = ptr - start;
    while (lex_size < 0)
        lex_size += BUFFER_SIZE;
    lexeme[(lex_size > MAX_LEX ? MAX_LEX : lex_size)] = '\0';
    if (lex_size > 20)
    {
        tkn.name = lEX_ERROR;
        return tkn;
    }

    switch (state)
    {
    case 2:
        tkn.name = lookup(lexeme);
        strcpy(tkn.id, lexeme);
        break;

    case 4:
        tkn.name = nUM;
        tkn.num = atoi(lexeme);
        break;

    case 7:
        tkn.name = rNUM;
        tkn.rnum = atof(lexeme);
        break;

    case 11:
        tkn.name = rNUM;
        tkn.rnum = atof(lexeme);
        break;

    case 12:
        tkn.name = nUM;
        tkn.num = atoi(lexeme);
        break;

    case 51:
        tkn.name = lEX_ERROR;
        strcpy(tkn.id, lexeme);
        break;
    }
    return tkn;
}

void lexer_reset(FILE *fp)
{
    state = 0;
    line_no = 0;
    ptr = 0;
    start = 0;
    Buffer[0] = '\0';
    to_be_scanned = 0;

    if (LOOKUP_SET == 0)
    {
        LOOKUP_SET = 1;
        populate_lookup();
    }
    fseek(fp, 0, SEEK_SET);
    populate_buffer(fp);
}

TOKEN eval_token(FILE *fp)
{
    char c;
    TOKEN tkn;
    while (c != EOF)
    {
        tkn.line = line_no;
        switch (state)
        {
        case 0:
            c = next_char(fp);
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
            else if (c == '$' && ptr == stop + 1)
            {
                tkn.name = $;
                strcpy(tkn.id, "EOF");
                return tkn;
            }
            else
            {
                state = 50;
            }

            break;

        case 1:
            c = next_char(fp);
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
            retract(1);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 3:
            c = next_char(fp);
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
            retract(1);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 5:
            c = next_char(fp);
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
                state = 51;
            }
            break;

        case 6:
            c = next_char(fp);
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
            retract(1);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 8:
            c = next_char(fp);
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
                state = 51;
            }
            break;

        case 9:
            c = next_char(fp);
            if (c >= '0' && c <= '9')
            {
                state = 10;
            }
            else
            {
                state = 51;
            }
            break;

        case 10:
            c = next_char(fp);
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
            retract(1);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 12:
            retract(2);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 13:
            c = next_char(fp);
            if (c == ' ' || c == '\t' || c == '\n')
            {
                state = 13;
                if (c == '\n')
                    line_no++;
            }
            else
            {
                state = 14;
            }
            break;

        case 14:
            retract(1);
            start = ptr;
            state = 0;
            break;

        case 15:
            tkn.name = pLUS;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "+", 20);
            return tkn;
            break;

        case 16:
            tkn.name = mINUS;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "-", 20);
            return tkn;
            break;

        case 17:
            c = next_char(fp);
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
            retract(1);
            tkn.name = mUL;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "*", 20);
            return tkn;
            break;

        case 19:
            c = next_char(fp);
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
            c = next_char(fp);
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
            tkn.name = dIV;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "/", 20);
            return tkn;
            break;

        case 23:
            c = next_char(fp);
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
            retract(1);
            tkn.name = lT;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "<", 20);
            return tkn;
            break;

        case 25:
            tkn.name = lE;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "<=", 20);
            return tkn;
            break;

        case 26:
            c = next_char(fp);
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
            retract(1);
            tkn.name = dEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "<<", 20);
            return tkn;
            break;

        case 28:
            tkn.name = dRIVERDEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "<<<", 20);
            return tkn;
            break;

        case 29:
            c = next_char(fp);
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
            retract(1);
            tkn.name = gT;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ">", 20);
            return tkn;
            break;

        case 31:
            tkn.name = gE;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ">=", 20);
            return tkn;
            break;

        case 32:
            c = next_char(fp);
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
            retract(1);
            tkn.name = eNDDEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ">>", 20);
            return tkn;
            break;

        case 34:
            tkn.name = dRIVERENDDEF;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ">>>", 20);
            return tkn;
            break;

        case 35:
            c = next_char(fp);
            if (c == '=')
            {
                state = 36;
            }
            else
            {
                state = 51;
            }
            break;

        case 36:
            tkn.name = eQ;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "==", 20);
            return tkn;
            break;

        case 37:
            c = next_char(fp);
            if (c == '=')
            {
                state = 38;
            }
            else
            {
                state = 51;
            }
            break;

        case 38:
            tkn.name = nE;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "!=", 20);
            return tkn;
            break;

        case 39:
            c = next_char(fp);
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
            tkn.name = aSSIGNOP;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ":=", 20);
            return tkn;
            break;

        case 41:
            retract(1);
            tkn.name = cOLON;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ":", 20);
            return tkn;
            break;

        case 42:
            c = next_char(fp);
            if (c == '.')
            {
                state = 43;
            }
            else
            {
                state = 51;
            }
            break;

        case 43:
            tkn.name = rANGEOP;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "..", 20);
            return tkn;
            break;

        case 44:
            tkn.name = sEMICOL;
            start = ptr;
            state = 0;
            strcpy(tkn.id, ";");
            return tkn;
            break;

        case 45:
            tkn.name = cOMMA;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ",", 20);
            return tkn;
            break;

        case 46:
            tkn.name = sQBO;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "[", 20);
            return tkn;
            break;

        case 47:
            tkn.name = sQBC;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "]", 20);
            return tkn;
            break;

        case 48:
            tkn.name = bO;
            start = ptr;
            state = 0;
            strncpy(tkn.id, "(", 20);
            return tkn;
            break;

        case 49:
            tkn.name = bC;
            start = ptr;
            state = 0;
            strncpy(tkn.id, ")", 20);
            return tkn;
            break;

        case 50:
            tkn.name = lEX_ERROR;
            /* strncpy(tkn.id, "error", 5); */
            strcpy(tkn.id, "error");
            start = ptr;
            state = 0;
            return tkn;
            break;

        case 51:
            retract(1);
            tkn = is_tkn(fp);
            start = ptr;
            state = 0;
            return tkn;
            break;

        default:
            break;
        }
    }
}

void remove_comments(FILE *ipt, char *opt_name)
{
    FILE *opt = fopen(opt_name, "w");
    int state = 0;
    char c = fgetc(ipt);

    while (c != EOF)
    {
        switch (state)
        {
        case 0:
            if (c == '*')
            {
                state = 1;
            }
            else
            {
                fputc(c, opt);
            }
            break;

        case 1:
            if (c == '*')
            {
                state = 2;
            }
            else
            {
                state = 0;
                fputc('*', opt);
                fputc(c, opt);
            }
            break;

        case 2:
            if (c == '*')
            {
                state = 3;
            }
            else
            {
                state = 2;
                if (c == '\n')
                {
                    fputc(c, opt);
                }
            }
            break;

        case 3:
            if (c == '*')
            {
                state = 0;
            }
            else
            {
                state = 2;
            }
            break;

        default:
            break;
        }
        c = fgetc(ipt);
    }

    fclose(opt);
}

void print_token_details(TOKEN curr, FILE *token_fp){
    if (curr.name == nUM)
    {
        if (token_fp != NULL) fprintf(token_fp, "LINE: [%d] ENUM: %d TOKEN: NUM       : %d \n", curr.line, curr.name, curr.num);
        printf("LINE: [%d] ENUM: %d TOKEN: NUM       : %d \n", curr.line, curr.name, curr.num);
    }
    else if (curr.name == rNUM)
    {
        if (token_fp != NULL) fprintf(token_fp, "LINE: [%d] ENUM: %d  TOKEN: RNUM      : %f \n", curr.line, curr.name, curr.rnum);
        printf("LINE: [%d] ENUM: %d  TOKEN: RNUM      : %f \n", curr.line, curr.name, curr.rnum);
    }
    else if (curr.name == $)
    {
        if (token_fp != NULL) fprintf(token_fp, "LINE: [%d] ENUM: %d  TOKEN: EOF/DOLLAR: %s\n", curr.line, curr.name, curr.id);
        printf("LINE: [%d] ENUM: %d  TOKEN: EOF/DOLLAR: %s\n", curr.line, curr.name, curr.id);
    }
    else if (curr.name == lEX_ERROR)
    {
        if (token_fp != NULL) fprintf(token_fp, "LINE: [%d] ENUM: %d  TOKEN: ERROR     : %s\n", curr.line, curr.name, curr.id);
        printf("LINE: [%d] ENUM: %d  TOKEN: ERROR     : %s\n", curr.line, curr.name, curr.id);
    }
    else
    {
        if (token_fp != NULL) fprintf(token_fp, "LINE: [%d] ENUM: %d  TOKEN: ID        : %s\n", curr.line, curr.name, curr.id);
        printf("LINE: [%d] ENUM: %d  TOKEN: ID/KEYW        : %s\n", curr.line, curr.name, curr.id);
    }
}

int test_lexer_run(char *program_file, char *tokenized_file)
{
    FILE *token_fp = fopen(tokenized_file, "w");
    FILE *test_fp = fopen(program_file, "r");

    lexer_reset(test_fp);
    TOKEN curr;
    TOKEN arr[200];
    int i = 0;
    curr.name = lEX_ERROR; // setting initially for multiple rounds of tests
    while (curr.name != $)
    {
        curr = eval_token(test_fp);
        arr[i] = curr;
        i++;
    }

    fprintf(token_fp, "\n\nTOKENIZATION COMPLETE:- %d TOKENS\n\n", i);
    printf("\n\nTOKENIZATION COMPLETE:- %d TOKENS\n\n", i);
    for (int j = 0; j < i; j++)
    {
        curr = arr[j];
        print_token_details(curr, token_fp);
        /* if (curr.name == nUM) */
        /* { */
        /*     fprintf(token_fp, "LINE: [%d] TOKEN: NUM       : %d \n", curr.line, curr.num); */
        /*     printf("LINE: [%d] TOKEN: NUM       : %d \n", curr.line, curr.num); */
        /* } */
        /* else if (curr.name == rNUM) */
        /* { */
        /*     fprintf(token_fp, "LINE: [%d] TOKEN: RNUM      : %f \n", curr.line, curr.rnum); */
        /*     printf("LINE: [%d] TOKEN: RNUM      : %f \n", curr.line, curr.rnum); */
        /* } */
        /* else if (curr.name == $) */
        /* { */
        /*     fprintf(token_fp, "LINE: [%d] TOKEN: EOF/DOLLAR: %s\n", curr.line, curr.id); */
        /*     printf("LINE: [%d] TOKEN: EOF/DOLLAR: %s\n", curr.line, curr.id); */
        /* } */
        /* else if (curr.name == lEX_ERROR) */
        /* { */
        /*     fprintf(token_fp, "LINE: [%d] TOKEN: ERROR     : %s\n", curr.line, curr.id); */
        /*     printf("LINE: [%d] TOKEN: ERROR     : %s\n", curr.line, curr.id); */
        /* } */
        /* else */
        /* { */
        /*     fprintf(token_fp, "LINE: [%d] TOKEN: ID        : %s\n", curr.line, curr.id); */
        /*     printf("LINE: [%d] TOKEN: ID        : %s\n", curr.line, curr.id); */
        /* } */
    }
    fclose(test_fp);
    fclose(token_fp);
    printf("\n\nSubroutine Complete:- %d TOKENS\n\n", i);
    return 1;
}

/* int main(){  */
/*     char* test_file_1 = "../tests/test_lexer_1.txt.uncommented.txt";  */
/*     char* tokenized_file = "test_tokenized.txt";  */
/*     test_lexer_run(test_file_1, tokenized_file);  */
/*     return 0;  */
/* }  */

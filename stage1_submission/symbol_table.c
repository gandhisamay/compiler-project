#include "parser.c"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SYMB_SIZE 1000
#define SYM_P 11
typedef struct symbol_table_element
{
    char id[50];
    bool isArray;
    terminals type;
    int arr_start;
    int arr_end;
    int offset;
    int declare_lineno;

} SYMBOL_TABLE_ELEMENT;

int symbol_table_code(char *id)
{
    int size = strlen(id);
    
    int code = 0;
    int pow = 1;
    
    for (int i = 0; i < size; i++)
    {

        code = (code + (id[i] - 'a' + 1) * pow) % SYMB_SIZE;
        pow = (pow * SYM_P) % SYMB_SIZE;
    }

    return code;
}

SYMBOL_TABLE_ELEMENT* search_symbol_table(char id[], SYMBOL_TABLE_ELEMENT* table[])
{
    int index = symbol_table_code(id);

    
    while (table[index] != NULL) {

    if (strcmp(table[index]->id, id) == 0) {
      return table[index];
    }

    ++index;
    index %= SYMB_SIZE;
  }

    return NULL;
}

SYMBOL_TABLE_ELEMENT* create_symbol_table_element(char id[], bool isArray, terminals type, int arr_start, int arr_end, int offset, int declare){
    SYMBOL_TABLE_ELEMENT* ele = (SYMBOL_TABLE_ELEMENT*)malloc(sizeof(SYMBOL_TABLE_ELEMENT));
    strcpy(ele->id,id);
    ele->isArray = isArray;
    ele->type = type;
    if(isArray){
        ele->arr_start = arr_start;
        ele->arr_end = arr_end;
    }
    else {
        ele->arr_end = -1;
        ele->arr_start = -1;
    }
    ele->offset = offset;
    ele->declare_lineno = declare;
    return ele;
}

void insert_symbol_table(SYMBOL_TABLE_ELEMENT* ele, SYMBOL_TABLE_ELEMENT* table[])
{
    printf("\n::\n");
    int index = symbol_table_code(ele->id);
    while (table[index] != NULL) {

    printf("\n::\n");
    ++index;
    index %= SYMB_SIZE;
  }

  table[index] = ele;
}

void print_symbol_table_element(SYMBOL_TABLE_ELEMENT* ele){
    printf("ID: %s, ISARRAY: %d, TYPE: %s, DECLARE_LINE: %d\n ARR_ST: %d, ARR_END: %d, OFFSET: %d\n",ele->id,ele->isArray,term_str[ele->type],ele->declare_lineno,ele->arr_start,ele->arr_end,ele->offset);
}
void print_symbol_table(SYMBOL_TABLE_ELEMENT* table[]){
    for (int i=0;i<SYMB_SIZE;i++){
        if(table[i]== NULL)continue;
        print_symbol_table_element(table[i]);
        printf("\n");
    }
}

// int main(){
//     printf("START");
//     SYMBOL_TABLE_ELEMENT* table[SYMB_SIZE];
//     // char* tmp = "hi";
//     SYMBOL_TABLE_ELEMENT* ele = create_symbol_table_element("hi",false,iNTEGER,0,0,3456);
//     SYMBOL_TABLE_ELEMENT* ele1 = create_symbol_table_element("hi1",false,iNTEGER,0,0,345);
//     SYMBOL_TABLE_ELEMENT *ele2 = create_symbol_table_element("hi2",true,bOOLEAN,0,84610,368456);
//     SYMBOL_TABLE_ELEMENT *ele3 = create_symbol_table_element("hi4",false,iNTEGER,0,0,36);
//     SYMBOL_TABLE_ELEMENT *ele4 = create_symbol_table_element("hi3",true,rEAL,46,530,3456);
//     // SYMBOL_TABLE_ELEMENT ele5 = create_symbol_table_element("hi5",false,iNTEGER,0,0,456);
//     insert_symbol_table(ele,table);
//     insert_symbol_table(ele1,table);
//     insert_symbol_table(ele2,table);
//     insert_symbol_table(ele3,table);
//     insert_symbol_table(ele4,table);
//     // insert_symbol_table(ele,table);


//     SYMBOL_TABLE_ELEMENT* test = search_symbol_table("hi2",table);
//     printf("id: %s\n offset: %d",test->id,test->offset);
//     return 0;
// }

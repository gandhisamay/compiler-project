#include "linked_list.h"
#include <stdbool.h>
#include <string.h>

#define SYMB_SIZE 1000
#define SYM_P 11
typedef struct symbol_table_element
{
    char *id;
    bool isArray;
    n_terminals type;
    int arr_start;
    int arr_end;
    int offset;

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

SYMBOL_TABLE_ELEMENT search_symbol_table(char *id, SYMBOL_TABLE_ELEMENT table[])
{
    int index = symbol_table_code(id);

    SYMBOL_TABLE_ELEMENT ele;

    return ele;
}

SYMBOL_TABLE_ELEMENT create_symbol_table_element(char* id, bool isArray, n_terminals type, int arr_start, int arr_end, int offset){
    SYMBOL_TABLE_ELEMENT ele;
    strcpy(ele.id,id);
    ele.isArray = isArray;
    ele.type = type;
    if(isArray){
        ele.arr_start = arr_start;
        ele.arr_end = arr_end;
    }
    else {
        ele.arr_end = -1;
        ele.arr_start = -1;
    }
    ele.offset = offset;
}

void insert_symbol_table(SYMBOL_TABLE_ELEMENT ele, SYMBOL_TABLE_ELEMENT table[])
{

    int index = symbol_table_code(ele.id);
    while (table[index].id != NULL) {

    ++index;
    index %= SYMB_SIZE;
  }

  table[index] = ele;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer_helper.h"


int hash_code(char s[])
{
    int size = strlen(s);
    int code = 0;
    int pow = 1;
    for (int i = 0; i < size; i++)
    {
        code = (code + (s[i] - 'a' + 1) * pow) % HASH_SIZE;
        pow = (pow * P) % HASH_SIZE;
    }
    return code;
}

terminals search(char key[], Element *table[])
{
    int index = hash_code(key);

    while (table[index] != NULL)
    {

        if (strcmp(table[index]->key, key) == 0){
            return table[index]->name;
        }

        ++index;
        index %= HASH_SIZE;
    }

    return iD;
}

void print_lt(Element *table[]){
    int i = 0;
    for(; i<HASH_SIZE; i++){
        if (table[i] != NULL) printf("At index %d, Key = %s, Enum = %d\n", i, table[i]->key, table[i]->name);
    }
}

void insert(char key[], terminals name, Element *table[])
{

    Element *item = (Element *)malloc(sizeof(Element));
    item->name = name;
    strcpy(item->key,key);

    int index = hash_code(key);

    while (table[index] != NULL && table[index]->key != NULL)
    {

        ++index;
        index %= HASH_SIZE;
    }

    table[index] = item;
}

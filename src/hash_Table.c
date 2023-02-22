#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper.h"

#define HASH_SIZE 64
#define P 7


// To be taken from data struct created by samay
typedef struct sym
{ 

} Symbol;

Symbol *Lookup_Table[HASH_SIZE];

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

Symbol *search(int key)
{
    int index = hashCode(key);

    while (Lookup_Table[index] != NULL)
    {

        if (Lookup_Table[index]->key == key)
            return Lookup_Table[index];

        ++index;
        index %= HASH_SIZE;
    }

    return NULL;
}

void insert(char key[], tokens name)
{

    Symbol *item = (Symbol *)malloc(sizeof(Symbol));
    item->name = name;
    item->key = key;

    int index = hash_code(key);

    while (Lookup_Table[index] != NULL && Lookup_Table[index]->key != -1)
    {

        ++index;
        index %= HASH_SIZE;
    }

    Lookup_Table[index] = item;
}
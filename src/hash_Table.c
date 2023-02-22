#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper.h"
#include "hash_table.h"




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

tokens search(char key[], Element *table[])
{
    int index = hash_code(key);

    while (table[index] != NULL)
    {

        if (table[index]->key == key)
            return table[index]->name;

        ++index;
        index %= HASH_SIZE;
    }

    return NULL;
}

void insert(char key[], tokens name, Element *table[])
{

    Element *item = (Element *)malloc(sizeof(Element));
    item->name = name;
    strcpy(item->key,key);

    int index = hash_code(key);

    while (table[index] != NULL && table[index]->key != -1)
    {

        ++index;
        index %= HASH_SIZE;
    }

    table[index] = item;
}
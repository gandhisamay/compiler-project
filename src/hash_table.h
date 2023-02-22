#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper.h"

#define HASH_SIZE 32
#define P 7


typedef struct ele
{   
    char key[20];
    tokens name;
} Element;


Element *Lookup_Table[HASH_SIZE];


int hash_code(char s[]);

tokens search(char key[], Element *table[]);

void insert(char key[], tokens name, Element *table[]);
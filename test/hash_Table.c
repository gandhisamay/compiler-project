/*
 * Group 22
 * Samay Gandhi 2020A7PS0299P
 * Mohit Makwana 2020A7PS0048P
 * Kathan Patel 2020A7PS0058P
 * Aditya Sheth 2020A7PS1511P
 * Aryan Chavan 2020A7PS1692P
 */




#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
@brief : Returns hash-code according to a hash function
@input : char*
@output : int
*/
int hash_code(char s[]) {
  int size = strlen(s);
  int code = 0;
  int pow = 1;
  for (int i = 0; i < size; i++) {
    code = (code + (s[i] - 'a' + 1) * pow) % HASH_SIZE;
    pow = (pow * P) % HASH_SIZE;
  }
  return code;
}

/*
@brief : Searches for a key in hash table
@input : char* , Element**
@output : terminals
*/
terminals search(char key[], Element *table[]) {
  int index = hash_code(key);

  while (table[index] != NULL) {

    if (strcmp(table[index]->key, key) == 0) {
      return table[index]->name;
    }

    ++index;
    index %= HASH_SIZE;
  }

  return iD;
}

/*
@brief : Prints the rentire hash table
@input : Element**
@output : void
*/
void print_lt(Element *table[]) {
  int i = 0;
  for (; i < HASH_SIZE; i++) {
    if (table[i] != NULL)
      printf("At index %d, Key = %s, Enum = %d\n", i, table[i]->key,
             table[i]->name);
  }
}

/*
@brief : Inserts new key-value pair in the hash table
@input : char* , terminals , Element**
@output : void
*/
void insert(char key[], terminals name, Element *table[]) {

  Element *item = (Element *)malloc(sizeof(Element));
  item->name = name;
  strcpy(item->key, key);

  int index = hash_code(key);

  while (table[index] != NULL && table[index]->key != NULL) {

    ++index;
    index %= HASH_SIZE;
  }

  table[index] = item;
}

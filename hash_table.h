/*
    General purpose hash table for my projects and things. Shouldnt need too
    much teaking to fit into other projects.

    Full implementation.

    filename: hash_table.h
*/

#define __SED_ERR__
#include "sedhead.h"
#include <assert.h>

/* change the size of the hash table to fit the project */
#define _TBL_SIZE_    5

/* sets all the pointers in the hash table to NULL. Allocats the table itself
   if not allready done.*/
#define table_init(increment, hashTable)                                    \
{                                                                           \
    if((hashTable) == NULL){                                                \
        (hashTable) = (hashTable_s*) malloc(sizeof(hashTable_s));}          \
                                                                            \
    for((increment) = 0; (increment) < _TBL_SIZE_; ++(increment)){          \
        hashTable[(increment)] = NULL;}                                     \
                                                                            \
    (increment) = 0;                                                        \
} /* end table_init */

typedef struct Node
{
    char *data;        /* holds character data */
    struct Node *next; /* points to the next struct in the chain */
} node_s;

typedef struct Hashtable
{
    struct Node **table; /* hash table */
} hashTable_s;

/* insert a new node into the hash table */
int32_t table_insert(hashTable_s *hTable, char *toAdd);

/* remove a node from the hash table */
int32_t hash_node_remove(hashTable_s *hTable, char *toRemove);

/* retrieves the address of the node in question. 
   returns: NULL if match was not found. node_s if match was found. 
   errors: */
node_s retrieve_match(char *toFind);

/* deallocate the entire hash table */
void dealloc_table(hashTable_s *hTable);

/* display all the contents of the hash table */
void hashtable_disp();

/* display chain */
void chain_disp(node_s *chain);

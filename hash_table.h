/*
    General purpose hash table for my projects and things. Shouldnt need too
    much teaking to fit into other projects.

    Full implementation.

    filename: hash_table.h
*/

#define __SED_ERR__
#include "sedhead.h"

/* change the size of the hash table to fit the project */
#define _TBL_SIZE_    5

/* sets all the pointers in the hash table to NULL */
#define table_init(increment, hashTable)                            \
{                                                                   \
    for((increment) = 0; (increment) < _TBL_SIZE_; ++(increment)){  \
        hashTable[i] = NULL;}                                       \
} /* end table_init */

typedef struct Node
{
    char *data;        /* holds character data */
    struct Node *next; /* points to the next struct in the chain */
} node_s;

typedef struct Hashtable
{
    struct Node *hashTable[TBL_SIZE]; /* hash table */
} hashtable_s;

/* insert a new node into the hash table */
int32_t insert_table();

/* remove a node from the hash table */
int32_t remove_table();

/* retrieves the address of the node in question. */
node_s retrieve_match();


/* deallocate the entire hash table */
int32_t dealloc_table();


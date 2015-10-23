/*
    General purpose hash table for my projects and things. Shouldnt need too
    much teaking to fit into other projects.

    Full implementation.

    filename: hash_table.c
*/

#include "hash_table.h"
/*#define NDEBUG*/
#include <assert.h>

/* initialize a node */
static inline void init_node(node_s *Restrict toInit)/*#{{{*/
{
    if(toInit == NULL)
    {
        toInit = (node_s*) malloc(sizeof(node_s));
        if(toInit == NULL){
            errExit("insert_table: malloc failure");}
    }

    toInit -> data = NULL;
} /* end node_init #}}} */

/* this can be easily altered when conforming to a different project.
   This copy's a nodes data (whever char* or struct *) into the node */
static inline void copy_node(node_s *Restrict to, char *newData)/*#{{{*/
{
    int32_t len = 0;

    if(newData == NULL){
        errnumExit(EINVAL, "copy_node: data in from is NULL. cannot copy.");}

    len = strlen(newData) + 1;

    if(to -> data == NULL){
        to -> data = (char*) malloc(sizeof(char) * len);}

    strncpy(to -> data, newData, len);
} /* end copy_node #}}} */

/* hash a string by adding up the total of the ascii characters and moding it
   by the size of the hash table to aquire the index. */
static int32_t hashString(char *keyString)/*#{{{*/
{
    int32_t i = 0;
    int32_t stringTotal = 0; /* all the characters in the string added up */
    int32_t keySize = strlen(keyString); /* size of keyString */

    for(/*i=0*/; i < keySize; ++i){
        stringTotal += keyString[i];}
    
    return stringTotal % _TBL_SIZE_;
} /* end hashString #}}} */

/* Retrieves a matching node based on the given data toFind.
   Returns: Pointer to matching node. NULL if node was not found.
   Errors: calls errExit if no table was passed into function */
node_s* retrieve_match(hashTable_s *hTable, char *toFind)/*#{{{*/
{
    int32_t index = 0; /* index result of hash */
    node_s *current = NULL;

    if(hTable == NULL){
        errExit("retrieve_match: Missing table");}
    
    /* get index */
    index = hashString(toFind);

    /* set current to hTable index. the head ptr */
    current = hTable -> table[index];
    
    /* if the index the node is at does exist, neither does the node */
    if(current == NULL){
        return NULL;}
    
    /* JAMES "TODO": just NOTE: checks if string data is there. change this 
                     when altering for specific project */
    while(current != NULL)
    {
        if(strcmp(current -> data, toFind) == 0){
            return current;}
        current = current -> next;
    }

    return NULL;
} /* end retrieve_match #}}} */

/* insert a new node into the hash table, inserts at head of chain.
   Returns: 1 on success, 0 if there was not enough room to malloc
   Errors : EINVAL, data was NULL. exit() will be called in this implementation
            with and appropriate message */
int32_t table_insert(hashTable_s *hTable, char *toAdd)/*#{{{*/
{
    node_s *temp = NULL;
    int32_t index = 0;

    temp = (node_s*) malloc(sizeof(node_s));
    if(temp == NULL)
    {
        errMsg("insert_table: malloc failure (-_-;)"); 
        return 0;
    } 

    init_node(temp);
    
    /* turn key value into an index */
    index = hashString(toAdd);

    /* adds a new node into the table */
    copy_node(temp, toAdd);

    temp -> next = hTable -> table[index];
    hTable -> table[index] = temp;
    
    return 1;
} /* end insert #}}} */

/* remove a node from the hash table.
   Returns: 1 on succes, 0 if node was not found.
   Errors: noerrExit if no table passed */
int32_t hash_node_remove(hashTable_s *hTable, char *toRemove)/*#{{{*/
{
    int32_t index = 0;  /* index result of hash */
    node_s *current = NULL;
    node_s *previous = NULL;

    if(hTable == NULL){
        noerrExit("hash_node_remove: Missing table");}

    index = hashString(toRemove);

    current = hTable -> table[index];
    if(current == NULL || toRemove == NULL){
        return 0;} 
    
    /* if the head pointer is the match, set the index to point to the next
       node, free the node, return.
       TODO: NOTE: will need to free the node differently depending on project
                   implementation */
    if(strcmp(current -> data, toRemove) == 0)
    {
        hTable -> table[index] = current -> next;
        free(current -> data);
        free(current);
        return 1;
    }
    
    /* go through the chain untill the match is found, then free */
    while(current -> next != NULL)
    {
        previous = current;
        if(strcmp(current -> data, toRemove) == 0)
        {
            previous -> next = current -> next;
            free(current -> data);
            free(current);
            return 1;
        } 
        current = current -> next;
    }
    
    return 0;
} /* end remove #}}} */

/* deallocate the entire hash table from memory. */
void dealloc_table(hashTable_s *hTable) /*#{{{*/
{
    node_s *tmpHead = NULL; /* gets set to a pntr index in table */
    node_s *nxtNode = NULL; /* gets set to the next node in a chain */
    int32_t i = 0;

    if(hTable != NULL)
    {
        /* remove each index's contents. Remove the chain of each pointer in the
           array */
        for(/*i=0*/; i < _TBL_SIZE_; ++i)
        {
            tmpHead = hTable -> table[i];

            /* free chain */
            while(tmpHead != NULL)
            {
                nxtNode = tmpHead -> next;
                if(nxtNode != NULL)
                {
                   tmpHead -> next = nxtNode -> next;
                   /* TODO: NOTE: data will need to be freed differently 
                                  depening on implementation */
                   free(nxtNode -> data);
                   free(nxtNode -> next);
                }
                else
                {  
                    assert(tmpHead -> next == NULL);
                    /* free the index of the node* data */
                    free(tmpHead);
                } /* end else */
            } /* end while */
        } /* end for */
    } /* end if */
    /* now that everything is free, free the table itself */
    free(hTable);
} /* end dealloc_table #}}} */

/* display all the contents of the hash table */
void hashtable_disp(hashTable_s *hTable)/*#{{{*/
{
    int32_t i = 0;

    for(/*i=0*/; i < _TBL_SIZE_; ++i)
    {
        printf("\nIndex numner: %d",i);
        fflush(stdout);
        chain_disp(hTable -> table[i]);
    } 
} /* end hashtable_disp #}}} */

/* display chain */
void chain_disp(node_s *chain)/*#{{{*/
{
    int32_t i = 0;

    if(chain == NULL){
        return;}

    do
    {
        ++i;
        printf("\nNode #%d\n%s", i, chain -> data);
        chain = chain -> next;
    }while(chain -> next != NULL);
} /* end chain_disp #}}} */

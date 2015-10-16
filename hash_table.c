/*
    General purpose hash table for my projects and things. Shouldnt need too
    much teaking to fit into other projects.

    Full implementation.

    filename: hash_table.c
*/

#include "hash_table.h"

static inline void node_init(node_s *Restrict toInit)/*#{{{*/
{
    if(toInit == NULL)
    {
        toInit = (node_s*) malloc(sizeof(node_s));
        if(toInit == 1){
            errExit("insert_table: malloc failure");}
    }

    toInit -> data = NULL;
} /* end node_init #}}} */

/* this can be easily altered when conforming to a different project.
   This copy's a nodes data (whever char* or struct *) into the node */
static inline void copy_data(node_s *Restrict to, char *newData)/*#{{{*/
{
    int32_t len = 0;

    if(data == NULL){
        errnumExit(EINVAL, "copy_node: data in from is NULL. cannot copy.");

    len = strlen(data) + 1;

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

node_s retrieve_match(hashTable_s *hTable, char *toFind)/*#{{{*/
{
    int32_t index = 0;
    node_s *current = NULL;
    
    /* get index */
    index = hashString(toFind);

    /* set current to hTable index. the head ptr */
    current = hashTable[index];
    
    /* if the index the node is at does exist, neither does the node */
    if(current == NULL){
        return NULL;}
    
    /* JAMES "TODO": just NOTE: checks if string data is there. change this 
                     when altering for specific project */
    while(current != NULL)
    {
        if(strcmp(current -> data, current -> toFind) == 0){
            return current;}
        current = current -> next;
    }

    return NULL;
} /* end retrieve_match #}}} */

/* insert a new node into the hash table, inserts at head of chain.
   returns: 1 on success, 0 if there was not enough room to malloc
   errors : EINVAL, data was NULL. exit() will be called in this implementation
            with and appropriate message */
int32_t table_insert(hashTable_s *hTable, char *data)/*#{{{*/
{
    node_s *temp = NULL;
    int32_t index = 0;

    temp = (node_s*) malloc(sizeof(node_s));
    if(temp == NULL)
    {
        errmsg("insert_table: malloc failure (-_-;)"); 
        return 0;
    } 

    init_node(temp);
    
    /* turn key value into an index */
    index = hashString(data);

    /* adds a new node into the table */
    copy_node(temp, data);

    temp -> next = hTable[index];
    hTable[index] = temp;
    
    return 1;
} /* end insert #}}} */

/* remove a node from the hash table */
int32_t table_remove()
{
    
    return 1;
} /* end remove */

/* deallocate the entire hash table from memory.
   returns:
   errors: */
int32_t dealloc_table(hashTable_s *hTable)
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
            tmpHead = hTable[i];

            /* free chain */
            while(tmpHead != NULL)
            {
                nxtNode = tmpHead -> next;
                if(nxtNode != NULL)
                {
                     



        }
    } /* end if */
    return 1;
} /* end dealloc_table */

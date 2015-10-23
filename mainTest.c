#define __SED_NUM__    /* string conversion functions */
#define __SED_ERR__    /* error functions */
#include "sedhead.h"

#include "hash_table.h"

#define NBUFF 10

/* arg1 = # of inserts, arg 2 = # of removals */
int main(int argc, char *argv[])
{
    hashTable_s *testTable = NULL;

    char *name = NULL;         /* name to be passed into table */
    uint32_t insertions = 0;   /* argv[1] */
    uint32_t removals = 0;     /* argv[2] */
    uint32_t i = 0;

    insertions = get32_t(argv[1], 0, "insertion value");
    removals   = get32_t(argv[2], 0, "removal value");
    
    /* initialize hash table */
    table_init(testTable);

    /* insert some names */
    for(i = 0; i < removals; ++i)
    {
        gen_string(name, NBUFF);
    }

    /* display the jazz after the insertion. */

    return 0;
}

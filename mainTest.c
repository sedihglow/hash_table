#define __SED_NUM__    /* string conversion functions */
#define __SED_ERR__    /* error functions */
#include "sedhead.h"

#include "hash_table.h"


/* arg1 = # of inserts, arg 2 = # of removals arg3 */
int main(int argc, char *argv[])
{
    hashTable_s *testTable = NULL;

    char *name = NULL;         /* name to be passed into table */
    uint32_t insertions = 0;   /* argv[1] */
    uint32_t removals = 0;     /* argv[2] */
    uint32_t totalData = 0;    /* total data count */
    uint32_t i = 0;

    /* initialize hash table */
    table_init(testTable);
    return 0;
}

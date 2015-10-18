/* 
    Tests the hash table for all the stuff.

    filename: testTable.c
*/

#include "hash_table.h"

int32_t main(int32_t argc, char *argv[])
{
    /* declare and initalize a hash table */
    hashTable_s *testTable = NULL;
    int32_t i = 0;          /* increment */
    
    table_init(i, testTable); 

    /* insert a bunch of junk into the hash table. */
    for(i = 0; i < 10; ++i)
    {
        table_insert(testTable, "TestString1");
    } 

    /* print the hash table, check results */
    hashtable_disp();

    /* retrieve some nodes that are in the table, and some that are not. 
       check that returns are accurate */

    /* remove some nodes from the table */

    /* print the hash table, check results */

    /* deallocate the entire hash table */
    
    /* Ensure the table is pointed to NULL with an assert */

    exit(EXIT_SUCCESS);
}

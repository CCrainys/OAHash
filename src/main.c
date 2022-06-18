#include <stdio.h>

#include "hash_table.h"

int main() {
    // define a new empty hash table
    hash_table_table * hash_table = hash_table_new();

    // processing here...
    hash_table_insert(hash_table, 1, 3456);
    printf( "Inserting (1,3456) into table.\n" );
    hash_table_insert(hash_table, 2, 9999);
    printf( "Inserting (2,9999) into table.\n" );
    hash_table_insert(hash_table, 3, 8000);
    printf( "Inserting (3,8000) into table.\n" );
    hash_table_insert(hash_table, 4, 6000 );
    printf( "Inserting (4,6000) into table.\n" );

    uint64_t lookup = hash_table_search(hash_table, 1);
    printf( "Value for 'Key1': %llu\n", lookup);
    hash_table_delete_key(hash_table, 1);

    lookup = hash_table_search(hash_table, 1);
    printf( "Value for 'Key1' after deletion: %llu\n", lookup);

    lookup = hash_table_search(hash_table, 6 );
    printf( "Value for '6': %llu\n", lookup );

    printf( "Size: %i\n", hash_table->count );
    printf( "Maximum Capacity: %i\n", hash_table->size );

    // delete the hash table we created
    hash_table_delete_table(hash_table);
}
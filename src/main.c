#include <stdio.h>

#include "hash_table.h"

int main() {
    // define a new empty hash table
    hash_table_table * hash_table = hash_table_new();

    // processing here...
    hash_table_insert(hash_table, "Key1", "Value1" );
    printf( "Inserting \"Key1\" and \"Value1\" into table.\n" );
    hash_table_insert(hash_table, "Key2", "Value2" );
    printf( "Inserting \"Key2\" and \"Value2\" into table.\n" );
    hash_table_insert(hash_table, "Key3", "Value3" );
    printf( "Inserting \"Key3\" and \"Value3\" into table.\n" );
    hash_table_insert(hash_table, "Key4", "Value4" );
    printf( "Inserting \"Key4\" and \"Value4\" into table.\n" );

    char * lookup = hash_table_search(hash_table, "Key1");
    printf( "Value for 'Key1': %s\n", lookup);
    hash_table_delete_key(hash_table, "Key1");

    lookup = hash_table_search(hash_table, "Key1");
    printf( "Value for 'Key1' after deletion: %s\n", lookup);

    lookup = hash_table_search(hash_table, "FAKE KEY" );
    printf( "Value for 'FAKE KEY': %s\n", lookup );

    printf( "Size: %i\n", hash_table->count );
    printf( "Maximum Capacity: %i\n", hash_table->size );

    // delete the hash table we created
    hash_table_delete_table(hash_table);
}
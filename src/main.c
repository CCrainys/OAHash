#include "hash_table.h"

int main() {
    // define a new empty hash table
    hash_table_table * hash_table = hash_table_new();
    // processing here...

    // delete the hash table we created
    hash_table_delete_table(hash_table);
}
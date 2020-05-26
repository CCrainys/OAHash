#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

// define initialisation function
static hash_table_item * hash_table_new_item(const char * k, const char * v) {
    hash_table_item * item = malloc(sizeof(hash_table_item)); // TODO: check malloc response

    item->key = strdup(k); // duplicate key
    item->value = strdup(v); // duplicate value

    return item;
}
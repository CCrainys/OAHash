#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

// define item initialisation function
static hash_table_item * hash_table_new_item(const char * k, const char * v) {
    hash_table_item * item = malloc(sizeof(hash_table_item)); // TODO: check malloc response

    item->key = strdup(k); // duplicate key
    item->value = strdup(v); // duplicate value

    return item;
}

// define table initialisation function
hash_table_table * hash_table_new() {
    hash_table_table * hash_table = malloc(sizeof(hash_table_table)); // TODO: check malloc response

    hash_table->count = 0;
    hash_table->items = calloc((size_t) hash_table->size, sizeof(hash_table_item *)); // TODO: check calloc response
    hash_table->size = 50; // TODO: add resize ability in future

    return hash_table;
}
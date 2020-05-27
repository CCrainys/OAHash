#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "hash_table.h"

// define item initialisation function
static hash_table_item * hash_table_new_item(const char * k, const char * v) {
    hash_table_item * item = malloc(sizeof(hash_table_item));

    // check result of the call to malloc
    if (item != NULL) {
        item->key = strdup(k); // duplicate key
        item->value = strdup(v); // duplicate value
    } else {
        printf("%s \n", "Malloc failed when creating hash table item");
    }

    return item;
}

// define table initialisation function
hash_table_table * hash_table_new() {
    hash_table_table * hash_table = malloc(sizeof(hash_table_table));

    // check result of the call to malloc
    if (hash_table != NULL) {
        hash_table->count = 0;
        hash_table->items = calloc((size_t) hash_table->size, sizeof(hash_table_item *));

        // check result of the items call to calloc
        if (hash_table->items != NULL) {
            hash_table->size = 50; // TODO: add resize ability in future
        } else {
            printf("%s \n", "Calloc failed when creating hash table items - hash table size set to 0");
            hash_table->size = 0;
        }

    } else {
        printf("%s \n", "Malloc failed when creating hash table");
    }

    return hash_table;
}

// define item deletion function
static void hash_table_delete_item(hash_table_item * item) {
    free(item->key);
    free(item->value);
    free(item);
}

// define table deletion function
void hash_table_delete_table(hash_table_table * hash_table) {
    // ensure hash table pointer is not null
    if (hash_table != NULL) {
        // check if we have any items to delete
        if (hash_table->count != 0) {
            // delete all items in the table
            for (int item_index = 0; item_index < hash_table->size; item_index++) {
                hash_table_item *item = hash_table->items[item_index];
                // determine if we must delete the item
                if (item != NULL) {
                    hash_table_delete_item(item);
                }
            }
        }

        // free up pointer to items
        free(hash_table->items);

        free(hash_table);
    }
}

// define hashing function
static int hash_table_hash(const char * key, const int prime, const int hash_table_size) {
    long hash_value = 0;
    const int key_length = strlen(key);
    for (int i = 0; i < key_length; i++) {
        hash_value += (long) pow(prime, key_length - (i + 1)) * key[i];
        hash_value = hash_value % hash_table_size;
    }
    return (int) hash_value;
}

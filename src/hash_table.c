#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"

// choose primes larger than our alphabet size - ie >128
int PRIME_1 = 131;
int PRIME_2 = 137;
// define a deleted item to help prevent breaks in the collision chain
static hash_table_item HASH_TABLE_DELETED_ITEM = {NULL, NULL};
// define table initial base size
int HASH_TABLE_INITIAL_BASE_SIZE = 2; // set to larger value for normal use

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
        hash_table->base_size = HASH_TABLE_INITIAL_BASE_SIZE;
        hash_table->items = calloc((size_t) hash_table->base_size, sizeof(hash_table_item *));

        // check result of the items call to calloc
        if (hash_table->items != NULL) {
            hash_table->size = hash_table->base_size; // TODO: add resize ability in future
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

// define double hashing function
static int hash_table_dh_get_hash(const char * s, const int hash_table_size, const int attempt_number) {
    const int hash_a = hash_table_hash(s, PRIME_1, hash_table_size);
    const int hash_b = hash_table_hash(s, PRIME_2, hash_table_size);

    // mitigate risk of hashing to same bucket by adding 1 to hash_b
    return (hash_a + (attempt_number * (hash_b + 1))) % hash_table_size;
}

// define table insert function
void hash_table_insert(hash_table_table * hash_table, const char * key, const char * value) {
    // create pointer to a new item
    hash_table_item * item = hash_table_new_item(key, value);
    if (item != NULL) {
        // get the index for the new item
        int index = hash_table_dh_get_hash(item->key, hash_table->size, 0);
        // determine if there is an item already at this index
        hash_table_item * item_at_index = hash_table->items[index];
        int attempt_number = 1;
        // while we're not at an empty or deleted index keep generating a new index
        while ((item_at_index != NULL) && (item_at_index != &HASH_TABLE_DELETED_ITEM)) {
            // check if current item's key is equal to our key
            if (strcmp(item_at_index->key, key) == 0) {
                // delete the item with our key
                hash_table_delete_item(item_at_index);
                // place our updated value for this key at the same index
                hash_table->items[index] = item;
                return;
            } else {
                index = hash_table_dh_get_hash(item->key, hash_table->size, attempt_number);
                // determine if there is an item already at the index
                item_at_index = hash_table->items[index];
                attempt_number++;
            }
        }
        // store the item in the free index
        hash_table->items[index] = item;
        hash_table->count++;
    } else {
        printf("%s \n", "Item could not be inserted as there was not enough memory to store it");
    }
}

// define table search function
char * hash_table_search(hash_table_table * hash_table, const char * key) {
    // get the index for the key
    int index = hash_table_dh_get_hash(key, hash_table->size, 0);
    // determine if there is an item already at this index
    hash_table_item * item_at_index = hash_table->items[index];
    int i = 1;
    // while we're not at an empty index, compare the key to the items key, then linearly search
    while (item_at_index != NULL) {
        // check the key of the item against the key searching for and we're not at a deleted item
        if ((strcmp(item_at_index->key, key) == 0) && (item_at_index != &HASH_TABLE_DELETED_ITEM)) {
            // found an item with a matching key - get the value
            return item_at_index->value;
        }
        // get next index using current attempt count
        index = hash_table_dh_get_hash(key, hash_table->size, i);
        // get the item at this index if exists
        item_at_index = hash_table->items[index];
        // increment the attempt number
        i++;
    }
    // key not present in the hash table
    return NULL;
}

// define table deletion function for given key
void hash_table_delete_key(hash_table_table * hash_table, const char* key) {
    // get the index for the key
    int index = hash_table_dh_get_hash(key, hash_table->size, 0);
    // determine if there is an item already at this index
    hash_table_item * item_at_index = hash_table->items[index];
    int i = 1;
    // while we're not at an empty index, compare the key to the items key, then linearly search
    while (item_at_index != NULL) {
        // ensure we're not at a deleted item
        if (item_at_index != &HASH_TABLE_DELETED_ITEM) {
            // check the key of the item against the key searching for
            if (strcmp(item_at_index->key, key) == 0) {
                // delete the item
                hash_table_delete_item(item_at_index);
                // change item index to point to the deleted item
                // do not wish to break the collision chain so need to know item has been deleted
                hash_table->items[index] = &HASH_TABLE_DELETED_ITEM;
            }
        }
        // get next index using current attempt count
        index = hash_table_dh_get_hash(key, hash_table->size, i);
        // get the item at this index if exists
        item_at_index = hash_table->items[index];
        // increment the attempt number
        i++;
    }
    // decrement the count now item deleted
    hash_table->count--;
}

// define table initialisation of given size function
static hash_table_table * hash_table_new_given_size(const int base_size) {
    hash_table_table * hash_table = malloc(sizeof(hash_table));

    // check result of the call to malloc
    if (hash_table != NULL) {
        hash_table->base_size = base_size;
        hash_table->size = get_next_prime(hash_table->base_size);

        hash_table->count = 0;
        hash_table->items = calloc((size_t) hash_table->size, sizeof(hash_table_item *));

        // check result of the items call to calloc
        if (hash_table->items == NULL) {
            printf("%s \n", "Calloc failed when creating hash table items - hash table size set to 0");
            hash_table->size = 0;
        }

    } else {
        printf("%s \n", "Malloc failed when creating hash table");
    }

    return hash_table;
}

// define table resize function
static void hash_table_resize(hash_table_table * hash_table, const int base_size) {
    if (base_size < HASH_TABLE_INITIAL_BASE_SIZE) {
        return;
    }
    // create a new hash table and copy across items
    hash_table_table * new_hash_table = hash_table_new_given_size(base_size);
    for (int index = 0; index < hash_table->size; index++) {
        hash_table_item * current_item = hash_table->items[index];
        if ((current_item != NULL) && (current_item != &HASH_TABLE_DELETED_ITEM)) {
            hash_table_insert(new_hash_table, current_item->key, current_item->value);
        }
    }

    // replace original hash table contents with those of the new one

    // copy across new hash table attributes
    hash_table->count = new_hash_table->count;
    hash_table->base_size = new_hash_table->base_size;

    // delete the new hash table after copying remaining attributes
    const int current_hash_table_size = hash_table->size;
    hash_table->size = new_hash_table->size;
    new_hash_table->size = current_hash_table_size;

    hash_table_item ** current_hash_table_items = hash_table->items;
    hash_table->items = new_hash_table->items;
    new_hash_table->items = current_hash_table_items;

    hash_table_delete_table(new_hash_table);
}
#ifndef SRC_HASH_TABLE_H
#define SRC_HASH_TABLE_H
#include<stdint.h>

// define item struct for key-value pairs
typedef struct {
    uint64_t *key;
    uint64_t *value;
} hash_table_item;

// define hash table struct
typedef struct {
    int size;
    int base_size;
    int count;
    hash_table_item ** items;
} hash_table_table;

// add function prototypes
static hash_table_item * hash_table_new_item(uint64_t k, uint64_t v);
hash_table_table * hash_table_new();

static void hash_table_delete_item(hash_table_item * item);
void hash_table_delete_table(hash_table_table * hash_table);
void hash_table_delete_key(hash_table_table * hash_table, uint64_t key);

static uint64_t hash_table_hash(uint64_t key, const int prime);

static uint64_t hash_table_dh_get_hash(uint64_t * s, const int hash_table_size, const int attempt_number);

void hash_table_insert(hash_table_table * hash_table, uint64_t key, uint64_t value);
uint64_t* hash_table_search(hash_table_table * hash_table, uint64_t key);

static void hash_table_resize_grow(hash_table_table * hash_table);
static void hash_table_resize_shrink(hash_table_table * hash_table);

#endif //SRC_HASH_TABLE_H
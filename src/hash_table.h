#ifndef SRC_HASH_TABLE_H
#define SRC_HASH_TABLE_H

// define item struct for key-value pairs
typedef struct {
    char * key;
    char * value;
} hash_table_item;

// define hash table struct
typedef struct {
    int size;
    int base_size;
    int count;
    hash_table_item ** items;
} hash_table_table;

// add function prototypes
static hash_table_item * hash_table_new_item(const char * k, const char * v);
hash_table_table * hash_table_new();

static void hash_table_delete_item(hash_table_item * item);
void hash_table_delete_table(hash_table_table * hash_table);
void hash_table_delete_key(hash_table_table * hash_table, const char * key);

static int hash_table_hash(const char * key, const int prime, const int hash_table_size);
static int hash_table_dh_get_hash(const char * s, const int hash_table_size, const int attempt_number);

void hash_table_insert(hash_table_table * hash_table, const char * key, const char * value);
char * hash_table_search(hash_table_table * hash_table, const char * key);

static void hash_table_resize_grow(hash_table_table * hash_table);
static void hash_table_resize_shrink(hash_table_table * hash_table);

#endif //SRC_HASH_TABLE_H
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
    int count;
    hash_table_item ** items;
} hash_table_table;

#endif //SRC_HASH_TABLE_H
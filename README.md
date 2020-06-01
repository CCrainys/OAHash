# C Hash Table

A hash table implemented in C utilising open addressing and double hashing.

[View Main Source (hash_table.c)](/src/hash_table.c)

## List of Functions

### Creation
`hash_table_new()` - returns `hash_table_table *` pointing to the created hash table  
`hash_table_new_item(const char * k, const char * v)` - returns `hash_table_item *` pointing to the created item

### Insertion
`hash_table_insert(hash_table_table * hash_table, const char * key, const char * value)`

### Search
`hash_table_search(hash_table_table * hash_table, const char * key)` - returns `char *` with the value at this key, `NULL` if key not found

### Deletion
`hash_table_delete_key(hash_table_table * hash_table, const char * key)`  
`hash_table_delete_table(hash_table_table * hash_table)`

## Example Usage

[The main.c file](/src/main.c) shows example usage of the hash table, direct calls to the new hash table, insert item, search by key, delete key and delete hash table functions are made.

A very low initial base size for the hash table was chosen in [hash_table.c](/src/hash_table.c) so the resizing function effects could be seen when running this example program. This obviously should be a much greater value in practice (than 2), say 50 - although this is obviously application dependent.

### Output
```sh
Inserting "Key1" and "Value1" into table.
Inserting "Key2" and "Value2" into table.
Inserting "Key3" and "Value3" into table.
Inserting "Key4" and "Value4" into table.
Value for 'Key1': Value1
Value for 'Key1' after deletion: (null)
Value for 'FAKE KEY': (null)
Size: 3
Maximum Capacity: 5

Process finished with exit code 0
```

## Implementation Details

Key-Value pairs are stored in a `struct`, our hash table then stores an array of pointers to items along with additional fields such as base size, capacity, and the number of items currently stored.

### Double Hashing

Double hashing is utilised to handle collisions. For `i` collisions, we determine an index using: 
`index = (hash_a(key) + (i * (hash_b(key) + 1))) % hash_table_size`

The value 1 is added to the result of the second hash to ensure we do not continuously try to insert at the same bucket. If the result of the second hash was 0, this would be the case no matter the value of `i`.

When updating values in the table, the original item is deleted and replaced by the new item.

### Resizing

The hash table resizes when load boundaries are crossed upon insert and deletion.

We resize up when the load is > 0.7, and resize down when the load is < 0.1. 
Resizing ~halves the table size when shrinking and ~doubles the table size when growing, all non-deleted items are inserted into this newly sized table.

Our new hash table size is a prime number to avoid clustering of values into a small number of buckets. Upon resize, we find the next prime after our new halved/doubled size.

### Malloc and Calloc

Malloc and Calloc checks are undertaken when reserving memory to check that memory has in fact been assigned, if this is not the case appropriate error messages are thrown.

#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct hash_table hash_table_t;
typedef struct hash_node hash_node_t;

hash_table_t* hash_create(size_t initial_capacity);
void hash_destroy(hash_table_t* table);
bool hash_insert(hash_table_t* table, const char* key, void* value);
void* hash_get(const hash_table_t* table, const char* key);
bool hash_delete(hash_table_t* table, const char* key);
size_t hash_size(const hash_table_t* table);

#endif

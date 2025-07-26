#include "hash.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct hash_table {
	struct hash_node** buckets;
	size_t capacity;
	size_t size;
	double load_factor_threshold;
};

struct hash_node {
	char* key;
	void* value;
	struct hash_node* next;
};

// internal helper functions
static size_t hash_function(const char* key, size_t capacity) {}
static void resize_table(hash_table_t* table) {}

// public functions
hash_table_t* hash_create(size_t initial_capacity) {}
void hash_destroy(hash_table_t* table) {}
bool hash_insert(hash_table_t* table, const char* key, void* value) {}
void* hash_get(hash_table_t* table, const char* key) {}
bool hash_delete(hash_table_t* table, const char* key) {}
size_t hash_size(hash_table_t* table) {}

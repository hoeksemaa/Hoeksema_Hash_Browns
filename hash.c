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
// static size_t hash_function(const char* key, size_t capacity) {
//	// TODO: implement hash_funciton
//	(void)key;
//	(void)capacity;
//	return 0;
// }

// static void resize_table(hash_table_t* table) {
//	// TODO: implement resize_table
//	(void)table;
// }

// public functions
hash_table_t* hash_create(size_t initial_capacity) {
	// allocate memory for hash table struct itself
	hash_table_t* table = malloc(sizeof(hash_table_t));
	if (table == NULL) {
		return NULL; // malloc failed
	}

	// allocate memory for the bucket array
	table->buckets = malloc(initial_capacity * sizeof(struct hash_node*));
	if (table->buckets == NULL) {
		free(table); // clean up if second malloc fails
		return NULL;
	}

	// initialize fields
	table->capacity = initial_capacity;
	table->size = 0;
	table->load_factor_threshold = 0.75;

	// initialize buckets to empty
	for (size_t i = 0; i < initial_capacity; i++) {
		table->buckets[i] = NULL;
	}

	return table;
}

void hash_destroy(hash_table_t* table) {
	if (table == NULL) {
		return; // nothing to destroy
	}

	// TODO: free all nodes in all buckets

	free(table->buckets);
	free(table);
}

bool hash_insert(hash_table_t* table, const char* key, void* value) {
	// TODO: implement hash_insert
	(void)table;
	(void)key;
	(void)value;
	return false;
}

void* hash_get(const hash_table_t* table, const char* key) {
	// TODO: implement hash_get
	(void)table;
	(void)key;
	return NULL;
}

bool hash_delete(hash_table_t* table, const char* key) {
	// TODO: implement hash_delete
	(void)table;
	(void)key;
	return false;
}

size_t hash_size(const hash_table_t* table) {
	if (table == NULL) {
		return 0;
	}
	return table->size;
}

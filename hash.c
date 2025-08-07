#define _POSIX_C_SOURCE 200809L

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
static size_t hash_function(const char* key) {

	// implementing djb2 hash algorithm
	size_t hash = 5381;
	int c;

	/* key is dereferenced for the char it points at
	 * and then the char is assigned to c.
	 * when c = '\0', the loop breaks. */
	while ((c = *key++)) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}

	return hash;
}

static hash_node_t* create_node(const char* key, void* value, hash_node_t* next) {
	
	// allocate for the node
	hash_node_t* node = malloc(sizeof(hash_node_t));
	if (!node) return NULL; 

	// allocate for the key string
	node->key = strdup(key);
	if (!node->key) {
		free(node);
		return NULL;
	}

	// copy but don't allocate for the value
	// the caller could pass us a pointer to data; we don't care what the data is or whether it changes
	node->value = value;
	node->next = next;
	return node;
}

static bool resize_table(hash_table_t* table) {
	
	// save old values
	hash_node_t** old_buckets = table->buckets;
	size_t old_capacity = table->capacity;

	// resize capacity and buckets
	table->buckets = calloc(table->capacity * 2, sizeof(hash_node_t*));
	if (!table->buckets) return false;
	table->capacity = table->capacity * 2;

	// rehash all existing nodes
	for (size_t i = 0; i < old_capacity; i++) {

		// for all nodes in the current bucket...
		hash_node_t* current = old_buckets[i];
		while (current) {

			// 1. save next node
			hash_node_t* next = current->next;

			// 2. rehash node
			size_t hash_value = hash_function(current->key);
			size_t bucket_index = hash_value % table->capacity;

			// 3. reassigning pointers
			current->next = table->buckets[bucket_index];
			table->buckets[bucket_index] = current;

			// 4. go to next node
			current = next;
		}
	}
	
	free(old_buckets);

	return true;
}

// public functions
hash_table_t* hash_create(size_t initial_capacity) {
	// we do a little input validation
	if (initial_capacity == 0) return NULL;

	// allocate memory for hash table struct itself
	hash_table_t* table = malloc(sizeof(hash_table_t));
	if (!table) {
		return NULL; // malloc failed
	}

	// allocate memory for the bucket array
	// calloc zeros the memory, so no initialization required
	table->buckets = calloc(initial_capacity, sizeof(hash_node_t*));
	if (!table->buckets) {
		free(table); // clean up if second malloc fails
		return NULL;
	}

	// initialize fields
	table->capacity = initial_capacity;
	table->size = 0;
	table->load_factor_threshold = 0.75;

	return table;
}

void hash_destroy(hash_table_t* table) {
	if (!table) {
		return; // nothing to destroy
	}

	for (size_t i = 0; i < table->capacity; i++) {
		hash_node_t* current = table->buckets[i];
		while (current) {
			hash_node_t* next = current->next;
			free(current->key);
			free(current);
			current = next;
		}
	}

	free(table->buckets);
	free(table);
}

bool hash_insert(hash_table_t* table, const char* key, void* value) {
	// we do a little defensive programming
	if (!table || !key) return false;

	// 1. perform resize if necessary
	if (table->size > table->capacity * table->load_factor_threshold) {
		bool resize_success = resize_table(table);
		if (!resize_success) return false;
	}

	// 2. hash key and find bucket
	size_t hash_value = hash_function(key);
	size_t bucket_index = hash_value % table->capacity;

	// 3. get the head of the linked list at this bucket
	hash_node_t* current = table->buckets[bucket_index];

	// 4. traverse chain to check if key already exists
	while (current) {

		// key exists; update value
		// no need for incrementing size or resizing
		if (strcmp(current->key, key) == 0) {
			current->value = value;
			return true;
		}
		current = current->next;
	}

	// 5. key doesn't exist; create new node
	hash_node_t* node = create_node(key, value, table->buckets[bucket_index]);
	if (!node) return false;
	table->buckets[bucket_index] = node;

	// 6. increment size
	table->size++;

	return true;
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
	if (!table) {
		return 0; // invalid table
	}
	return table->size;
}

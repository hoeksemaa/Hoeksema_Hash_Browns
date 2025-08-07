#include "hash.h"
#include <stdio.h>
#include <assert.h>

void test_create_size_destroy();
void test_insert();

int main() {
	test_create_size_destroy();
	test_insert();
	return 0;
}

void test_create_size_destroy() {
	
	// test create
	printf("Testing hash_create()...\n");

	hash_table_t* table = hash_create(16);
	assert(table != NULL);
	
	printf("✓ hash_create() works\n");

	// test size
	printf("Testing hash_size()...\n");
	
	size_t size = hash_size(table);
	assert(size == 0);
	
	printf("✓ hash_size() works\n");

	// test destroy
	printf("Testing hash_destroy()...\n");
	
	hash_destroy(table);
	
	printf("✓ hash_destroy() completed without crashing\n");
}

void test_insert() {
	
	// creating table
	printf("Creating hash_table of capacity 4...\n");
	hash_table_t* table = hash_create(4);
	size_t size = hash_size(table);
	char* key = "1";
	void* value = "dog";
	bool insert_success;
	assert(size == 0);

	// inserting +1
	printf("Inserting 1...\n");
	insert_success = hash_insert(table, key, value);
	size = hash_size(table);
	assert(size == 1);
	
	// inserting +2
	printf("Inserting 2...\n");
	key = "2";
	insert_success = hash_insert(table, key, value);
	printf("Inserting 3...\n");
	key = "3";
	insert_success = hash_insert(table, key, value);
	size = hash_size(table);
	assert(size == 3);

	// inserting +3 (should trigger resize; also more nodes than buckets)
	printf("Inserting 4...\n");
	key = "4";
	insert_success = hash_insert(table, key, value);
	printf("Inserting 5...\n");
	key = "5";
	insert_success = hash_insert(table, key, value);
	printf("Inserting 6...\n");
	key = "6";
	insert_success = hash_insert(table, key, value);
	size = hash_size(table);
	assert(size == 6);

	printf("✓ hash_insert() works\n");

	(void)insert_success;
}

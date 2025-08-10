#include "hash.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_create_size_destroy();
void test_insert();
void test_delete();
void test_get();

int main() {
	test_create_size_destroy();
	test_insert();
	test_delete();
	test_get();
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

void test_delete() {

	// create table
	printf("Creating hash_table with 2 keys inserted...\n");
	hash_table_t* table = hash_create(4);
	char* key = "1";
	void* value = "dog";
	bool insert_success;
	bool delete_success;

	insert_success = hash_insert(table, key, value);
	key = "2";
	insert_success = hash_insert(table, key, value);
	size_t size = hash_size(table);
	assert(size == 2);
	printf("✓ created table of size 2.\n");

	// delete object
	printf("Deleting key = 1 from table\n");
	delete_success = hash_delete(table, "1");
	size = hash_size(table);
	assert(size == 1);
	printf("✓ hash_delete() works\n");

	(void)insert_success;
	(void)delete_success;
}

void test_get() {
	
	// create table
	printf("Creating table of with 2 keys inserted...\n");
	hash_table_t* table = hash_create(4);
	char* key = "1";
	void* value = "cat";
	bool insert_success;

	insert_success = hash_insert(table, key, value);
	key = "2";
	insert_success = hash_insert(table, key, value);
	size_t size = hash_size(table);
	assert(size == 2);
	printf("✓ created table of size 2.\n");

	// get object
	printf("Preparing to hash_get()...\n");
	void* retrieved = hash_get(table, key);
	assert(strcmp((char*)retrieved, "cat") == 0);
	//printf(value_gotten);
	//printf("\n");
	printf("✓ hash_get() works\n");

	(void)insert_success;
}

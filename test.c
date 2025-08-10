#include "hash.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define TEST(name, condition) \
	printf("[%s] Testing %s.\n", (condition) ? "PASS" : "FAIL", name)

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
	
	// table creation
	hash_table_t* table = hash_create(16);
	TEST("hash_create()", table != NULL);
	
	// table size
	size_t size = hash_size(table);
	TEST("hash_size()", size == 0);
	
	// table destroy
	hash_destroy(table);
	TEST("hash_destroy() doesn't crash", true);	
}

void test_insert() {
	
	// creating table
	hash_table_t* table = hash_create(4);
	size_t size = hash_size(table);
	char* key = "1";
	void* value = "dog";
	bool insert_success;
	TEST("hash_create() of capacity 4", size == 0);

	// inserting +1
	insert_success = hash_insert(table, key, value);
	size = hash_size(table);
	TEST("hash_insert() 1x", size == 1);

	// inserting +2
	key = "2";
	insert_success = hash_insert(table, key, value);
	size = hash_size(table);
	TEST("hash_insert() 2x", size == 2);
	
	// inserting +3
	key = "3";
	insert_success = hash_insert(table, key, value);
	size = hash_size(table);
	TEST("hash_insert() 3x (should trigger resize)", size == 3);

	// inserting +4, 5, 6 (should trigger resize; also more nodes than buckets)
	key = "4";
	insert_success = hash_insert(table, key, value);
	key = "5";
	insert_success = hash_insert(table, key, value);
	key = "6";
	insert_success = hash_insert(table, key, value);
	size = hash_size(table);
	TEST("hash_insert() 6x (should trigger second resize)", size == 6);

	(void)insert_success;
}

void test_delete() {

	// create table
	hash_table_t* table = hash_create(4);
	char* key = "1";
	void* value = "dog";
	bool insert_success;
	bool delete_success;

	insert_success = hash_insert(table, key, value);
	key = "2";
	insert_success = hash_insert(table, key, value);
	size_t size = hash_size(table);
	TEST("hash_create() of capacity 4", size == 2);

	// delete object
	delete_success = hash_delete(table, "1");
	size = hash_size(table);
	TEST("hash_delete()", size == 1);
	assert(size == 1);

	(void)insert_success;
	(void)delete_success;
}

void test_get() {
	
	// create table
	hash_table_t* table = hash_create(4);
	char* key = "1";
	void* value = "cat";
	bool insert_success;

	insert_success = hash_insert(table, key, value);
	key = "2";
	insert_success = hash_insert(table, key, value);
	size_t size = hash_size(table);
	assert(size == 2);

	// get object
	void* retrieved = hash_get(table, key);
	TEST("hash_get()", strcmp((char*)retrieved, "cat") == 0);

	(void)insert_success;
}

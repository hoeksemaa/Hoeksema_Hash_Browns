#include "hash.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define TEST(name, condition) \
	printf("[%s] Testing %s\n", (condition) ? "PASS" : "FAIL", name)
#define TABLE_CAPACITY 4

void test_create_size_destroy();
void test_insert_and_retrieve();
void test_delete();
void test_resize();

int main() {
	test_create_size_destroy();
	test_insert_and_retrieve();
	test_delete();
	test_resize();
	return 0;
}

void test_create_size_destroy() {

	printf("\nCREATE, SIZE, DESTROY TEST\n");	

	size_t size;

	// table creation
	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);
	
	// table size
	size = hash_size(table);
	TEST("hash_size()", size == 0);
	
	// table destroy
	hash_destroy(table);
	TEST("hash_destroy() doesn't crash", true);	
}

void test_insert_and_retrieve() {

	printf("\nINSERT AND RETRIEVE TEST\n");

	size_t size;
	bool insert_success;
	void* retrieve_success;

	// creating table
	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);

	// insert
	insert_success = hash_insert(table, "1", "cat");
	TEST("hash_insert() success for '1':'cat'", insert_success);
	size = hash_size(table);
	TEST("table size", size == 1);

	// retrieve
	retrieve_success = hash_get(table, "1");
	TEST("hash_get() success for key: '1'", retrieve_success);
	TEST("hash_get() value = 'cat'", strcmp((char*)retrieve_success, "cat") == 0);

	hash_destroy(table);
}

void test_delete() {

	printf("\nOBJECT DELETE TEST\n");

	bool insert_success;
	bool delete_success;

	// create table
	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);

	insert_success = hash_insert(table, "1", "cat");
	TEST("hash_insert() success", insert_success);
	insert_success = hash_insert(table, "2", "dog");
	TEST("hash_insert() success", insert_success);
	size_t size = hash_size(table);
	TEST("table of size 2", size == 2);

	// delete object
	delete_success = hash_delete(table, "1");
	TEST("hash_delete() success", delete_success);
	size = hash_size(table);
	TEST("table of size 1", size == 1);

	hash_destroy(table);
}

void test_resize() {

	printf("\nTABLE RESIZE TEST\n");

	bool insert_success;
	size_t size;

	// create table
	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create() with table capacity 4", table != NULL);
	
	// one insert
	insert_success = hash_insert(table, "1", "cat");
	TEST("hash_insert() success", insert_success);
	size = hash_size(table);
	TEST("table size == 1", size == 1);

	// four more inserts
	insert_success = hash_insert(table, "2", "dog");
	TEST("hash_insert() success", insert_success);
	insert_success = hash_insert(table, "3", "rat");
	TEST("hash_insert() success", insert_success);
	insert_success = hash_insert(table, "4", "snake");
	TEST("hash_insert() success", insert_success);
	insert_success = hash_insert(table, "5", "bird");
	TEST("hash_insert() success", insert_success);

	// check final size
	size = hash_size(table);
	TEST("table size == 5", size == 5);
		
	hash_destroy(table);
}	

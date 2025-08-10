#include "hash.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"
#define TEST(name, condition) \
	do { \
		if (condition) { \
			printf(COLOR_GREEN "[PASS]" COLOR_RESET " %s\n", name); \
		} else { \
			printf(COLOR_RED "[FAIL]" COLOR_RESET " %s\n", name); \
		} \
	} while(0)
#define TITLE(text) \
	printf(" > %s\n", text)
#define TABLE_CAPACITY 4

void test_create_size_destroy();
void test_insert_and_retrieve();
void test_delete();
void test_resize();
void test_duplicate_key();
void test_duplicate_keys();
void test_get_nonexistent_key();
void test_delete_nonexistent_key();
void test_insert_null_key();
void test_insert_empty_key();

int main() {
	
	// core tests	
	test_create_size_destroy();
	test_insert_and_retrieve();
	test_delete();
	test_resize();

	// edge cases
	test_duplicate_keys();
	test_get_nonexistent_key();
	test_delete_nonexistent_key();
	test_insert_null_key();
	test_insert_empty_key();
	return 0;
}

void test_create_size_destroy() {

	TITLE("CREATE, SIZE, DESTROY TEST");	

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

	TITLE("INSERT AND RETRIEVE TEST");

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

	TITLE("OBJECT DELETE TEST");
	
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

	TITLE("TABLE RESIZE TEST");
	
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

void test_duplicate_keys() {
	
	TITLE("DUPLICATE KEYS TEST");
	
	size_t size;
	bool insert_success;
	void* retrieve_success;

	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);

	// insert same key three times
	insert_success = hash_insert(table, "1", "cat");
	TEST("hash_insert() success for '1':'cat'", insert_success);
	insert_success = hash_insert(table, "1", "cat");
	TEST("hash_insert() success for '1':'cat'", insert_success);
	insert_success = hash_insert(table, "1", "dog");
	TEST("hash_insert() success for '1':'dog'", insert_success);

	size = hash_size(table);
	TEST("table size == 1", size == 1);

	retrieve_success = hash_get(table, "1");
	TEST("hash_get() value = 'dog'", strcmp((char*)retrieve_success, "dog") == 0);

	hash_destroy(table);
}

void test_get_nonexistent_key() {
	
	TITLE("GET NONEXISTENT KEY TEST");
	
	void* retrieve_success;

	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);

	retrieve_success = hash_get(table, "1");
	TEST("hash_get() returns NULL", !retrieve_success);

	hash_destroy(table);
}

void test_delete_nonexistent_key() {

	TITLE("DELETE NONEXISTENT KEY TEST");
	
	bool delete_success;

	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);

	delete_success = hash_delete(table, "1");	
	TEST("hash_delete() return false", !delete_success);

	hash_destroy(table);
}

void test_insert_null_key() {

	TITLE("INSERT NULL KEY TEST");
	
	bool insert_success;

	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);

	char* key = NULL;
	insert_success = hash_insert(table, key, "cat");
	TEST("hash_insert() returns false", !insert_success);

	hash_destroy(table);
}

void test_insert_empty_key() {

	TITLE("INSERT EMPTY KEY TEST");
	
	bool insert_success;

	hash_table_t* table = hash_create(TABLE_CAPACITY);
	TEST("hash_create()", table != NULL);

	insert_success = hash_insert(table, "", "cat");
	TEST("hash_insert() returns true", insert_success);

	hash_destroy(table);
}


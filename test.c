#include "hash.h"
#include <stdio.h>
#include <assert.h>

void test_create_size_destroy();

int main() {
	test_create_size_destroy();
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

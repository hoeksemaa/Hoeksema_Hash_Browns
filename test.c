#include "hash.h"
#include <stdio.h>
#include <assert.h>

void test_create();

int main() {
	test_create();
	return 0;
}

void test_create() {
	printf("Testing hash_create()...\n");

	hash_table_t* table = hash_create(16);
	assert(table != NULL);

	printf("✓ hash_create() works\n");
}

#include "hash.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	srand(0);

	//int random_num = rand(); // on my system, this number is 2147483647

	size_t breakpoint = 1000000;
	size_t size_max = 1000000000;
	size_t table_size;
	size_t num;
	char key[16];
	int* value;
	time_t current_time, past_time, delta_time;

	hash_table_t* table = hash_create(16);
	printf("> RANDOM KEY INSERTION BEGUN\n");
	current_time = time(NULL);

       	for (size_t i = 0; i < size_max; i++) {
		// check for breakpoint
		if (i % breakpoint == 0) {
			table_size = hash_size(table);

			// get current time
			past_time = current_time;
			current_time = time(NULL);
			delta_time = difftime(current_time, past_time);
			printf("%ld insertions; table size: %ld; current time: %ld s; delta time: %ld s\n", i, table_size, current_time, delta_time);
		}

		// insert random key and value
		num = rand();
		snprintf(key, sizeof(key), "%ld", num);
		value = malloc(sizeof(int));
		*value = num;
		hash_insert(table, key, value);
				
	}	

	return 0;
}

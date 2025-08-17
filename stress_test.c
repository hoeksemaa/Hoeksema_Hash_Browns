#include "hash.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	srand(0);

	size_t breakpoint = 2000000;
	size_t size_max = 1000000000;
	size_t num;
	char key[16];
	int* value;
	time_t start_time, current_time, past_time, delta_time;

	hash_table_t* table = hash_create(16);
	printf("> RANDOM KEY INSERTION BEGUN\n");
	start_time = time(NULL);
	current_time = time(NULL);

       	for (size_t i = 0; i < size_max; i++) {
		// every X insertions, print out table status and time
		if (i % breakpoint == 0) {
			// get current time
			past_time = current_time;
			current_time = time(NULL);
			delta_time = difftime(current_time, past_time);
			
			// large test message
			printf("insertions: %10ld       current size: %10ld       time: %3lds       delta time: %3lds\n", i, hash_size(table), current_time - start_time, delta_time);
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

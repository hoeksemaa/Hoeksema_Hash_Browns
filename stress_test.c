#include "hash.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	srand(0);

	//int random_num = rand(); // on my system, this number is 2147483647

	size_t breakpoint = 1000;
	size_t size_max = 1000000000;
	size_t num;
	char key[16];
	int* value;

	
	hash_table_t* table = hash_create(16);

       	for (size_t i = 0; i < size_max; i++) {
		// get random key and value
		num = rand();
		snprintf(key, sizeof(key), "%ld", num);
		value = malloc(sizeof(int));
		*value = num;
		
		// insert random keys
		hash_insert(table, key, value);

		// check for breakpoint
		if (i % breakpoint == 0) {
			printf("inserted # key %d\n", (int)i);
		}		
	}	

	/*
	time_t start_time, end_time;

	start_time = time(NULL);
	char* time_string = ctime(&start_time);
	printf("current time: %s\n", time_string);
	
	sleep(4);

	printf("current time: %s\n", time_string);

	end_time = time(NULL);
	char* time_end = ctime(&end_time);
	printf("current time: %s\n", time_end);

	(void)start_time;
	//(void)end_time;\
	*/

	return 0;
}

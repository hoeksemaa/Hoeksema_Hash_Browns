#include "hash.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	time_t start_time, end_time;

	start_time = time(NULL);

	sleep(4);

	end_time = time(NULL);

	(void)start_time;
	(void)end_time;
	return 0;
}

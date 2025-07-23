CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

test: test.c hash.c hash.h
	$(CC) $(CFLAGS) -o test test.c hash.c

clean:
	rm -f test

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGETS = test stress_test

all: $(TARGETS)

test: test.c hash.c
	$(CC) $(CFLAGS) -o $@ $^

stress_test: stress_test.c hash.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)

.PHONY: all clean

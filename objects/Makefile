CC = gcc
CFLAGS = -Wall -g -O2

.DEFAULT_GOAL = all

all:
	$(MAKE) -C src all
	gcc test.c -o test_main -L. -lfoxobjects
	@echo "To test run './test_main'"

clean:
	$(MAKE) -C src clean
	rm -f test_main
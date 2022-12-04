CC = gcc
CFLAGS = -Wall -g -O2

.DEFAULT_GOAL = all

all:
	$(MAKE) -C src all
	gcc test.c -o test_main -L. -lfoxconfig
	@echo "To test run './test_main test/example.foxconfig'"

install-extension:
	cp -rf ./foxconfig-0.0.1 ~/.vscode/extensions/

uninstall-extension:
	rm -rf ~/.vscode/extensions/foxconfig-0.0.1

clean:
	$(MAKE) -C src clean
	rm -f test_main
CC = gcc
CFLAGS = -Wall -g -O2
OBJ = foxobjects.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	ar rcs ../libfoxobjects.a $(OBJ)

clean:
	rm -f *.o
	rm -f ../libfoxobjects.a

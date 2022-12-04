CC = gcc
CFLAGS = -Wall -g -O2
OBJ = FoxString.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	ar rcs ../libfoxstring.a $(OBJ)

clean:
	rm -f *.o
	rm -f ../libfoxstring.a

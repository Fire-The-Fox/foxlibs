CC = gcc
CFLAGS = -Wall -g -O2
OBJ = array.o dict.o parser.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	ar rcs ../libfoxconfig.a $(OBJ)

clean:
	rm -f *.o
	rm -f ../libfoxconfig.a
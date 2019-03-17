CC=gcc
CFLAGS=-g -Wall

all: fib_error fib foo

fib_error: fib_error.c
	$(CC) $(CFLAGS) fib_error.c -o fib_error -lm

fib: fib.c
	$(CC) $(CFLAGS) fib.c -o fib -lm

foo: foo.c
	$(CC) $(CFLAGS) foo.c -o foo

clean:
	rm fib_error fib foo


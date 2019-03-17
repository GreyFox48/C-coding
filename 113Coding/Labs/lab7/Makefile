CC=gcc
CFLAGS=-g -Wall

all: str test basic array side string_error swap dynamic dbl

test: test.o str.o
	$(CC) $(CFLAGS) test.o str.o -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

str: str.c str.h
	$(CC) $(CFLAGS) -c str.c

basic: basic.c
	$(CC) $(CFLAGS) basic.c -o basic

array: array.c
	$(CC) $(CFLAGS) array.c -o array

side: side.c
	$(CC) $(CFLAGS) side.c -o side

string_error: string_error.c
	$(CC) $(CFLAGS) string_error.c -o string_error

swap: swap.c
	$(CC) $(CFLAGS) swap.c -o swap 

dynamic: dynamic.c str
	$(CC) $(CFLAGS) dynamic.c str.o -o dynamic 

dbl: dbl.c
	$(CC) $(CFLAGS) dbl.c -o dbl 

clean: 
	rm str.o test test.o basic array side string_error swap dynamic dbl

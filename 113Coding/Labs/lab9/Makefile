CC=gcc
CFLAGS=-g -Wall

all: dllist cpu lab9

dllist: dllist.c dllist.h
	$(CC) $(CFLAGS) -c dllist.c

cpu: cpu.c cpu.h
	$(CC) $(CFLAGS) -c cpu.c

lab9: cpu dllist lab9.c
	$(CC) $(CFLAGS) dllist.o cpu.o lab9.c -o lab9

clean:
	rm lab9 cpu.o dllist.o

CC=gcc
CFLAGS=-g -Wall
APUE=$(HOME)/Dropbox/222Coding/apue.src.3e/apue.3e
INC_PATH=-I$(APUE)/include
LIB_PATH=-L$(APUE)/lib
LIB=-lapue

all: holes tee wc zeros hexdump dup2

tee: tee.c read_all
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) read_all.o $@.c $(LIB) -o $@

wc: wc.c read_all
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) read_all.o $@.c $(LIB) -o $@

holes: holes.c read_all
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) read_all.o $@.c $(LIB) -o $@

zeros: zeros.c read_all
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) read_all.o $@.c $(LIB) -o $@

hexdump: hexdump.c read_all
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) read_all.o $@.c $(LIB) -o $@

dup2: dup2.c
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) $@.c $(LIB) -o $@

read_all: read_all.c read_all.h
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) -c $@.c $(LIB)

clean:
	rm holes tee



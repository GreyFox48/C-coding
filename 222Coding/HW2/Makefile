CC=gcc
CFLAGS=-g -Wall
APUE=$(HOME)/Dropbox/222Coding/apue.src.3e/apue.3e
INC_PATH=-I$(APUE)/include
LIB_PATH=-L$(APUE)/lib
LIB=-lapue

all: secs_apue secs secs_to_date myenv

secs_apue: secs_apue.c
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) $@.c $(LIB) -o $@

secs: secs.c
	$(CC) $(CFLAGS) $@.c -o $@

date: date.c date.h
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) -c $@.c $(LIB)

secs_to_date: date secs_to_date.c
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) date.o $@.c $(LIB) -o $@

myenv: myenv.c
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) $@.c $(LIB) -o $@

clean:
	rm secs secs_apue date.o secs_to_date myenv



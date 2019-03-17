CC=gcc
CFLAGS=-g -Wall

all: dec2hex hex2dec

dec2hex: dec2hex.c
	$(CC) $(CFLAGS) $@.c -o $@ 

hex2dec: hex2dec.c
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm dec2hex hex2dec


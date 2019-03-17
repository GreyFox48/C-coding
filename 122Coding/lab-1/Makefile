CC=gcc
FLAGS=-g -Wall

all: kml lab11

lab11: kml lab11.c kml.h
	$(CC) $(FLAGS) lab11.c kml.o -o lab11 

kml: kml.c kml.h
	$(CC) $(FLAGS) -c kml.c

clean:
	rm lab11 kml.o

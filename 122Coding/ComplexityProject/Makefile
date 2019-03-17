CC = gcc
CFLAGS = -g -Wall

all: main.o blackbox.o
	$(CC) $(CFLAGS) -o complexity_project main.o blackbox.o

main.o: complexity_project.c
	$(CC) $(CFLAGS) -c -o main.o complexity_project.c -o complexity_project

clean:
	rm main.o

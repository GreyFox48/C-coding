CC=gcc
CFLAGS=-g -Wall

targets = test_qsort heapsort test_heap repeated scrabble_bsearch test_heap_int
all: $(targets)

heapsort: heapsort.c
	$(CC) $(CFLAGS) -c $@.c

test_heap: test_heap.c heapsort
	$(CC) $(CFLAGS) $@.c heapsort.o -o $@
	
test_heap_int: test_heap_int.c heapsort
	$(CC) $(CFLAGS) $@.c heapsort.o -o $@
	
scrabble_bsearch: scrabble_bsearch.c
	$(CC) $(CFLAGS) $@.c -o $@

%: %.c
	$(CC) $(CFLAGS) $@.c -o $@

.PHONY: clean
clean:
	rm -rf *.o $(targets)

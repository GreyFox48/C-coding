CC=gcc
CFLAGS=-g -Wall

#add test_stack to all target once you have written the stack library
all: lex postfix stack test_stack lex_lisp bal_paren

lex: lex.c lex.h
	$(CC) $(CFLAGS) -c $@.c

postfix: postfix.c lex stack
	$(CC) $(CFLAGS) $@.c lex.o stack.o -o $@ -lm

stack: stack.c stack.h
	$(CC) $(CFLAGS) -c $@.c

test_stack: test_stack.c stack
	$(CC) $(CFLAGS) $@.c stack.o -o $@
	
lex_lisp: lex_lisp.c lex_lisp.h
	$(CC) $(CFLAGS) -c $@.c
	
bal_paren: bal_paren.c lex_lisp stack
	$(CC) $(CFLAGS) $@.c lex_lisp.o stack.o -o $@ 

clean:
	rm -rf *.o postfix test_stack bal_paren

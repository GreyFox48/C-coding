CFLAGS=-g
AS=as
ASFLAGS=-gen-debug
LD=ld
LINK=-dynamic-linker /lib64/ld-linux-x86-64.so.2

all: up prime_stack gcd prime_bss prime_odd caesar et_tu_brute

up: up.s
	as $(CFLAGS) up.s -o up.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc up.o -o up

caesar: caesar.s
	as $(CFLAGS) caesar.s -o caesar.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc caesar.o -o caesar

et_tu_brute: et_tu_brute.s
	as $(CFLAGS) et_tu_brute.s -o et_tu_brute.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc et_tu_brute.o -o et_tu_brute

prime_stack: prime_stack.s
	as $(CFLAGS) prime_stack.s -o prime_stack.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc prime_stack.o -o prime_stack

prime_bss: prime_bss.s
	as $(CFLAGS) prime_bss.s -o prime_bss.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc prime_bss.o -o prime_bss

prime_odd: prime_odd.s
	as $(CFLAGS) prime_odd.s -o prime_odd.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc prime_odd.o -o prime_odd

gcd: gcd.s
	as $(CFLAGS) gcd.s -o gcd.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc gcd.o -o gcd

clean:
	rm -rf *.o up 

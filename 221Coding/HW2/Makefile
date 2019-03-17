CFLAGS= -g

all: cpuid_write cpuid_printf cpuid1 foo

cpuid_write: cpuid_write.s
	as $(CFLAGS) cpuid_write.s -o cpuid_write.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc cpuid_write.o -o cpuid_write

cpuid_printf: cpuid_printf.s
	as $(CFLAGS) cpuid_printf.s -o cpuid_printf.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc cpuid_printf.o -o cpuid_printf

cpuid1: cpuid1.s
	as $(CFLAGS) cpuid1.s -o cpuid1.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc cpuid1.o -o cpuid1

foo: foo.s
	as $(CFLAGS) foo.s -o foo.o
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc foo.o -o foo



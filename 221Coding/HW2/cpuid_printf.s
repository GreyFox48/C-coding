# as $(CFLAGS) cpuid_printf.s -o cpuid_printf.o
# ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc cpuid_printf.o -o cpuid_printf

.section .data
output:
	.asciz "The processor Vendor ID is '%s'\n"
.section .bss
	.lcomm buffer, 12
.section .text
.globl _start
_start:

movl $0, %eax
cpuid

movl $buffer, %edi
movl %ebx, (%edi)
movl %edx, 4(%edi)
movl %ecx, 8(%edi)

movq $output, %rdi
movq $buffer, %rsi
movq $0, %rax

call printf

movq $0, %rdi
call exit

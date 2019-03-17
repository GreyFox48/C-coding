.section .data
output:
	.asciz "The processor Vendor ID is 'xxxxxxxxxxxx'\n"
.section .bss

.section .text
.globl _start
_start:

movl $0, %eax
cpuid

movq $output, %rdi
movl %ebx, 28(%rdi)
movl %edx, 32(%rdi)
movl %ecx, 36(%rdi)
movq $1, %rax #call write function
movq $1, %rdi #write to STDOUT
movq $42, %rdx #pass count size
movq $output, %rsi #start of string  
syscall

movq $60, %rax #call exit
syscall

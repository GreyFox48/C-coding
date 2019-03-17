.section .data
output:
	.asciz "%d\n"
.section .bss

.section .text
.globl _start
_start:
movq $37, %rdi # value of a
movq $3, %rsi # value of b
movq $0, %rax # was unsure if own functions needed to set rax to zero if no floats
cmp %rdi, %rsi
jle body #jump if a >= b
movq %rdi, %r12 #switch if not
movq %rsi, %rdi
movq %r12, %rsi

body:
cmp $0, %rsi
je gcd # being zero signifies gcd in rsi (a is gcd)
movq %rdi, %rax
xorq %rdx, %rdx
divq %rsi #determine a%b
movq %rsi, %rdi 
movq %rdx, %rsi # new order for body function is body (b, remainder)
movq $0, %rax
call body #loop
jmp end

gcd:
mov %rdi, %rax #store answer in rax
ret

end:
movq %rax, %rsi
movq $0, %rax
movq $output, %rdi #get ready to print and exit
call printf
movq $0, %rdi
call exit

.section .data
output1:
	.asciz "The answer is %d\n"
output2:
	.asciz "No, the answer is %d\n"
.section .bss

.section .text
.globl _start
_start:

subq $32, %rsp
movq $10, (%rsp) #save variables to stack, variable x
movq $20, 8(%rsp) #variable y
movq $3, 16(%rsp) #variable z
movq $0, 24(%rsp) #variable ans

movq (%rsp), %rdi #load variables into registers for calling
movq 8(%rsp), %rsi
movq 16(%rsp), %rdx
movq $0, %rax

call foo

movq %rax, %rsi #print first output
movq $output1, %rdi
pushq %rsi #save rsi value for later
movq $0, %rax
call printf

popq %rsi
movq $output2, %rdi #print second output
incq %rsi
movq $0, %rax
call printf


addq $32, %rsp #clear stack
movq $0, %rdi
call exit

foo:
subq $16, %rsp
movq $29, (%rsp) #x value
movq $50, 8(%rsp) #y value
movq (%rsp), %rax #push on x

movq %rdx, %r8 #save rdx value
cqto
idivq 8(%rsp) #mod by y
movq %rdx, %rbx #save mod value
movq %r8, %rdx #restore rdx value

movq %rsi, %rax
imulq %rdx

addq %rdi, %rax
subq %rbx, %rax

addq $16, %rsp #deallocate stack
ret

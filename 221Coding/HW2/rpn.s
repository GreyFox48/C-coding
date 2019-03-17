.section .data

.section .bss

.section .text
.globl _start
_start:
pushq $8
pushq $2

popq %rax
popq %rbx
addq %rbx, %rax

pushq %rax
pushq $6

popq %rbx
popq %rax
mulq %rbx

pushq %rax
pushq $12

popq %rbx
popq %rax
addq %rbx,%rax

pushq %rax
pushq $2

popq %rbx
popq %rax
cqto
idivq %rbx

pushq %rax
pushq $1
pushq $3

popq %rax
popq %rbx
addq %rbx,%rax

pushq %rax

popq %rbx
popq %rax
subq %rbx,%rax

pushq %rax
pushq $4

popq %rbx
popq %rax
cqto
idivq %rbx

pushq %rdx

popq %rdi
movq $60,%rax
syscall 


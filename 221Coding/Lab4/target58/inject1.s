.section .data

.section .bss

.section .text
.globl _start
_start:

movq $0x1037a0ef, %rdi
movq $0x401711, (%rsp)
ret


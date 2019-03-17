.section .data
outputID:
	.asciz "cpuid eax value: 0x%x\n"
outputFN:
	.asciz "extended family number: 0x%x\n"
outputMN:
	.asciz "extneded model number:  0x%x\n"
outputP:
	.asciz "processor: 0x%x\n"
outputF:
	.asciz "family: 0x%x\n"
outputM:
	.asciz "model: 0x%x, %d\n"
outputSI:
	.asciz "stepping_id: 0x%x\n"
.section .bss
	
.section .text
.globl _start
_start:

movl $1, %eax
cpuid
pushq %rax

movq $outputID, %rdi
movq (%rsp), %rsi
movq $0, %rax
call printf

movq $outputFN, %rdi
movq (%rsp), %rsi
andl $0x0ff00000, %esi
shrl $20, %esi
movq $0, %rax
call printf

movq $outputMN, %rdi
movq (%rsp), %rsi
andl $0xf0000, %esi
shrl $16, %esi
movq $0, %rax
call printf

movq $outputP, %rdi
movq (%rsp), %rsi
andl $0x00003000, %esi
shrl $12, %esi
movq $0, %rax
call printf

movq $outputF, %rdi
movq (%rsp), %rsi
andl $0x0ff00000, %esi
shrl $20, %esi
movq (%rsp), %rbx
andl $0xf00, %ebx
shrl $8, %ebx
addl %ebx, %esi
movq $0, %rax
call printf

movq $outputM, %rdi
movq (%rsp), %rsi
andl $0xf0000, %esi
shrl $12, %esi
movq (%rsp), %rbx
andl $0xf0, %ebx
shrl $4, %ebx
addl %ebx, %esi
movl %esi, %edx
movq $0, %rax
call printf

movq $outputSI, %rdi
movq (%rsp), %rsi
andl $0xf, %esi
movq $0, %rax
call printf

movq $0, %rdi
call exit

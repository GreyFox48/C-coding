.section .data
string:
	.asciz "%d\n"
.section .bss

.section .text
.globl _start
_start:
movq $100, %rbx #arbritary number to set upper limit
movq %rbx, %r14 
leaq (, %r14, 4), %r15
and $-16, %r15
subq %r15, %rsp #byte align array
movl $0, %eax # prepare to make array
movq $0, %r12

#create the array of values
initialize:
incl %eax
movl %eax, (%rsp, %r12, 4)
incq %r12
#ensure index value does not exceed 
cmpq %rbx, %r12
jl initialize #increment and jump till beginning till out of specified limit

movq $0, %r12 #start at first index, (though will be purposefully skipped)
search_array:
incq %r12
cmp %rbx, %r12 #ensure not out of bounds
jge print_start #start printing if out of range
movl (%rsp, %r12, 4), %r13D
cmpl $0, %r13D #skip over zero values
movl %r13D, %r15D #prepare for incrementing later
jg remove_factors
jmp search_array

remove_factors:
addl %r13D, %r15D #increment value
movq %r15, %rax
cmp %rbx, %rax
jg search_array
leaq -4(%rsp, %r15, 4), %rax #calcultes address based on factor, -4 to help with zero indexing
movl $0, (%rax)
jmp remove_factors

print_start:
movq $0, %r12 #for creating initial value

print:
# increment and determine if over size, if then jump to end
incq %r12 
cmp %rbx, %r12
jge end

#prepare for printing
movq $string, %rdi
movq $0, %rax
movl (%rsp, %r12, 4), %esi

#skip if value is zero 
cmpl $0, %esi 
je print

#print and repeat loop
call printf
jmp print

#end program
end:
movq $0, %rdi
call exit

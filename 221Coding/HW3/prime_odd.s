.section .data
string:
	.asciz "%d\n"
.section .bss
	.lcomm array, 800000000
.section .text
.globl _start
_start:
movq $200000000, %rbx #arbritary number to set upper limit 
movq $1, %r12
movl $2, %eax
leaq array(, %r12, 4), %r15 #ensure 2 is included in array
movl %eax, (%r15)
movl $-1, %eax
movq $0, %r12

#create the array of values
initialize:
addl $2, %eax
leaq array(, %r12, 4), %r15
movl %eax, (%r15)
addq $2, %r12 #just skip every other element
#ensure index value does not exceed 
cmpq %rbx, %r12
jl initialize #increment and jump till beginning till out of specified limit

movq $0, %r12 #start at second index, (though will be purposefully skipped)
search_array:
addq $2, %r12
movq %r12, %r15
imul %r15, %r15 #find square of index value
cmp %rbx, %r15 #ensure not out of bounds
jge print_start #start printing if out of range
movl array(, %r12, 4), %r13D #find p
leal (, %r13D, 2), %r15D #prepare 2p for incrementing later
imul %r13D, %r13D #obtain p^2 to start at
movl $0, %r14D # for indexing in later function
cmpl $0, %r13D #skip over zero values
jg remove_factors
jmp search_array

remove_factors:
movl %r15D, %eax
imull %r14D, %eax #find x*2p
movl %eax, %ecx
addl %r13d, %ecx #find the value to factor out
cmpq %rbx, %rcx #ensure not over limit value
jg search_array
leaq array(, %rcx, 4), %rax #find the value in memory
leaq -4(%rax), %rax #account for zero indexing
movl $0, (%rax)
incq %r14 #increment x in x*2p
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
movl array(, %r12, 4), %esi

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

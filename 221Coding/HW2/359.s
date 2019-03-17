store_prod:
movq %rdx, %rax #copy the y value to %rax
cqto #fill %rdx with the upper bits (sign bits) of %rax
movq %rsi, %rcx #copy x to %rcx 
sarq $63, %rcx #fill rcx with sign bits of x (sign extend %rsi)
imulq %rax, %rcx #multoply the low bits of y with the high bits of x
imulq %rsi, %rdx #multiply the low bits of x with the high bits of y
addq %rdx, %rcx #add the results of the low and high bit multiplications
mulq %rsi # multiply the usigned bits of %rax with %rsi, with multiplies the low bits of x and y
addq %rcx, %rdx # add low-high bit multiplications with high bits of both low-bit multiplications
movq %rax, (%rdi) # store the lower half of the result at the *dest address
movq %rdx, 8(%rdi) # store the high bits of the multiplition above the low bits at *dest
ret # exit function

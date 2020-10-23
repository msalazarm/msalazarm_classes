 
      #  this program calculates the sum of squares up to and including a user inputted number
      # marco salazar
      # 04/17/2020
      # sumuser.asm
      # the algorithm is a simple loop
      # input is the users number
      # output is the correct sum of squares to the inputted number
      # assumption that the sum of squares of the number given will not overflow
        
.data
str: .asciiz "The sum from 0 .. "
str1: .asciiz " is \n"
.align 0
                  

 .text  # directive that we are in the code segment

main:
        subu $a0, $sp, 20 # We want 5 mem locations for main SP, RA, i , s, and the user inputted value
        sw $ra, 4($a0)  # we need to store the RA in the Activation record
        sw $sp, ($a0) # store SP
        move $sp, $a0  # adjust SP

        sw $0, 8($sp)  # store 0 into memory -- counting variable 
        sw $0, 12($sp)  # store 0 into memory -- accumulating variable

	#reads one integer from user and saves in t0
	li $v0, 5
	syscall
	sw $v0 16($sp) #store the user number
 
       
loop:
        lw $t6, 8($sp)  #   i
        mul $t7, $t6, $t6  #  i * i
        lw $t8, 12($sp)   #  s
        addu $t9, $t8, $t7  #  s + i*i
        sw $t9, 12($sp)  #   s= s + i*i 
        lw $t6, 8($sp)   # i 
        addu $t0, $t6, 1  # i+1
        sw $t0, 8($sp)  #  i = i + 1
        lw $t1, 16($sp) # read the user number
        ble $t0, $t1, loop  #   keep doing it until the user number is reached
        nop   # 
        
        la $a0, str
        li $v0 4  #   print the begining string
        syscall # 
        nop   # 
        
        lw $a0, 16($sp)
        li $v0 1  #   print the user number
        syscall # 
        nop   # 
        
        la $a0, str1
        li $v0 4  #   print the end string
        syscall # 
        nop   # 
        
        lw $a0, 12($sp)
        li $v0 1 #   Print the sum of squares
        syscall
        
       
        lw $ra, 4($sp)
        lw $sp , ($sp)  # put backl Ra and SP
        
        li $v0, 10 
        syscall     #  exit for MAIN only


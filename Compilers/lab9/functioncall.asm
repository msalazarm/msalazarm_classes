.data
_L0:	 .asciiz	"inside f"
_NL:	 .asciiz	"\n"

.align 2
x4:	 .space	400

.text

.globl main

f:				# start of Function
		subu $a0, $sp, 12		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		la $a0 _L0		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a1 0		#not array, so index is 0
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a1 0		#not array, so index is 0
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		jr $ra		#jump back to the previous context
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		jr $ra		#jump back to the previous context
main:				# start of Function
		subu $a0, $sp, 20		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		li $a0, 2		# expression is a NUMBER
		sw $a0 12($sp)		# store s1 in temporary spot
		subu $t2, $sp, 12		# adjust the stack for function setup
		lw $a0 12($sp)		# load one of the paramaters
		sw $a0 8($t2)		# load one of the paramaters
		jal f		#jump to the function
		sw $a0 16($sp)		# move value to be assigned temporarily
		li $a1 0		#not array, so index is 0
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 16($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		li $a1 0		#not array, so index is 0
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		li $v0, 10		# leave MAIN program
		syscall		# Leave MAIN

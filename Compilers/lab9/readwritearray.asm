.data
_L0:	 .asciiz	"enter X"
_NL:	 .asciiz	"\n"

.align 2

.text

.globl main

main:				# start of Function
		subu $a0, $sp, 60		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		li $a0, 0		# expression is a NUMBER
		sw $a0 32($sp)		# move value to be assigned temporarily
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 32($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
_L1:				# check while condition
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 36($sp)		# store s1 in temporary spot
		li $a0, 5		# expression is a NUMBER
		move $a1 $a0		#move a0 to a1
		lw $a0 36($sp)		# load a0 with the temp value
		slt $a0 $a0 $a1		# is a0 < a1
		li $t0 0		#flag to compare against for branching
		beq $a0 $t0 _L2		# if false jump out of while statement
		la $a0 _L0		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		li $v0, 5		# read a number from input
		syscall		# system call for print number
		sw $v0, ($a0)		#store the number in memory
				
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 40($sp)		# store s1 in temporary spot
		li $a0, 1		# expression is a NUMBER
		move $a1 $a0		#move a0 to a1
		lw $a0 40($sp)		# load a0 with the temp value
		add $a0 $a0 $a1		# perform addition
		sw $a0 44($sp)		# move value to be assigned temporarily
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 44($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		j _L1		#go back to back to check to while expression
_L2:				# exit while clause
		li $a0, 0		# expression is a NUMBER
		sw $a0 40($sp)		# move value to be assigned temporarily
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 40($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
_L3:				# check while condition
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 44($sp)		# store s1 in temporary spot
		li $a0, 5		# expression is a NUMBER
		move $a1 $a0		#move a0 to a1
		lw $a0 44($sp)		# load a0 with the temp value
		slt $a0 $a0 $a1		# is a0 < a1
		li $t0 0		#flag to compare against for branching
		beq $a0 $t0 _L4		# if false jump out of while statement
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 48($sp)		# store s1 in temporary spot
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		move $a1 $a0		#move a0 to a1
		lw $a0 48($sp)		# load a0 with the temp value
		mult $a0 $a1		# preform multiplication
		mflo $a0		# save the lower multiplication in a0
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 52($sp)		# store s1 in temporary spot
		li $a0, 1		# expression is a NUMBER
		move $a1 $a0		#move a0 to a1
		lw $a0 52($sp)		# load a0 with the temp value
		add $a0 $a0 $a1		# perform addition
		sw $a0 56($sp)		# move value to be assigned temporarily
		li $a1 0		#not array, so index is 0
		add $a1 $a1 28		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 56($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		j _L3		#go back to back to check to while expression
_L4:				# exit while clause
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		li $v0, 10		# leave MAIN program
		syscall		# Leave MAIN

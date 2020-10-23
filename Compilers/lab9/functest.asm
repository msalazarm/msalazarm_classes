.data
_L0:	 .asciiz	"should be 0 and 0"
_L1:	 .asciiz	"should be 75"
_L2:	 .asciiz	"should be 2"
_L3:	 .asciiz	"should be 0"
_L4:	 .asciiz	"should be 5"
_NL:	 .asciiz	"\n"

.align 2

.text

.globl main

func:				# start of Function
		subu $a0, $sp, 20		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		li $a0, 2		# expression is a NUMBER
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		jr $ra		#jump back to the previous context
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		jr $ra		#jump back to the previous context
main:				# start of Function
		subu $a0, $sp, 112		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		la $a0 _L0		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a0, 0		# expression is a NUMBER
		sw $a0 52($sp)		# move value to be assigned temporarily
		li $a0, 0		# expression is a NUMBER
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 52($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		li $a0, 0		# expression is a NUMBER
		sw $a0 56($sp)		# move value to be assigned temporarily
		li $a0, 2		# expression is a NUMBER
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 56($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		li $a0, 0		# expression is a NUMBER
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a0, 2		# expression is a NUMBER
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a0, 75		# expression is a NUMBER
		sw $a0 60($sp)		# move value to be assigned temporarily
		li $a1 0		#not array, so index is 0
		add $a1 $a1 48		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 60($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		la $a0 _L1		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a1 0		#not array, so index is 0
		add $a1 $a1 48		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a0, 2		# expression is a NUMBER
		sw $a0 72($sp)		# store s1 in temporary spot
		li $a0, 1		# expression is a Boolean
		sw $a0 68($sp)		# store s1 in temporary spot
		li $a1 0		#not array, so index is 0
		add $a1 $a1 48		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 64($sp)		# store s1 in temporary spot
		subu $t2, $sp, 20		# adjust the stack for function setup
		lw $a0 72($sp)		# load one of the paramaters
		sw $a0 8($t2)		# load one of the paramaters
		lw $a0 68($sp)		# load one of the paramaters
		sw $a0 12($t2)		# load one of the paramaters
		lw $a0 64($sp)		# load one of the paramaters
		sw $a0 16($t2)		# load one of the paramaters
		jal func		#jump to the function
		sw $a0 76($sp)		# move value to be assigned temporarily
		li $a1 0		#not array, so index is 0
		add $a1 $a1 48		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 76($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		la $a0 _L2		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a1 0		#not array, so index is 0
		add $a1 $a1 48		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a0, 2		# expression is a NUMBER
		sw $a0 100($sp)		# store s1 in temporary spot
		li $a0, 1		# expression is a Boolean
		sw $a0 96($sp)		# store s1 in temporary spot
		li $a1 0		#not array, so index is 0
		add $a1 $a1 48		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 92($sp)		# store s1 in temporary spot
		subu $t2, $sp, 20		# adjust the stack for function setup
		lw $a0 100($sp)		# load one of the paramaters
		sw $a0 8($t2)		# load one of the paramaters
		lw $a0 96($sp)		# load one of the paramaters
		sw $a0 12($t2)		# load one of the paramaters
		lw $a0 92($sp)		# load one of the paramaters
		sw $a0 16($t2)		# load one of the paramaters
		jal func		#jump to the function
		sw $a0 104($sp)		# store s1 in temporary spot
		li $a0, 3		# expression is a NUMBER
		move $a1 $a0		#move a0 to a1
		lw $a0 104($sp)		# load a0 with the temp value
		add $a0 $a0 $a1		# perform addition
		sw $a0 108($sp)		# move value to be assigned temporarily
		li $a0, 2		# expression is a NUMBER
		sw $a0 88($sp)		# store s1 in temporary spot
		li $a0, 1		# expression is a Boolean
		sw $a0 84($sp)		# store s1 in temporary spot
		li $a1 0		#not array, so index is 0
		add $a1 $a1 48		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		sw $a0 80($sp)		# store s1 in temporary spot
		subu $t2, $sp, 20		# adjust the stack for function setup
		lw $a0 88($sp)		# load one of the paramaters
		sw $a0 8($t2)		# load one of the paramaters
		lw $a0 84($sp)		# load one of the paramaters
		sw $a0 12($t2)		# load one of the paramaters
		lw $a0 80($sp)		# load one of the paramaters
		sw $a0 16($t2)		# load one of the paramaters
		jal func		#jump to the function
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a1 108($sp)		# load a1 saved expression
		sw $a1 ($a0)		# save value in memory
		la $a0 _L3		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a0, 0		# expression is a NUMBER
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
		add $a1 $a1 8		# add index + location of beginning of array from sp
		add $a0, $sp, $a1		# identifier is a scaler
				
		lw $a0 ($a0)		# fetch value for the var
		li $v0, 1		# print the number
		syscall		# system call for print number
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		la $a0 _L4		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
		li $a0, 2		# expression is a NUMBER
		move $a1 $a0		#index of the array
		sll $a1 $a1 2		#shift index twice to left for Word Size
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

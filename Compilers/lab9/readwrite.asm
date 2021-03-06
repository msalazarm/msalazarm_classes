.data
_L0:	 .asciiz	"enter X"
_L1:	 .asciiz	" x is "
_NL:	 .asciiz	"\n"

.align 2

.text

.globl main

main:				# start of Function
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
				
		li $v0, 5		# read a number from input
		syscall		# system call for print number
		sw $v0, ($a0)		#store the number in memory
				
		la $a0 _L1		# load a0 with the string address
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
				
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		li $v0, 10		# leave MAIN program
		syscall		# Leave MAIN

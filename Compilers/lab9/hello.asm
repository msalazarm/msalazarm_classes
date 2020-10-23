.data
_L0:	 .asciiz	"hello world"
_NL:	 .asciiz	"\n"

.align 2

.text

.globl main

main:				# start of Function
		subu $a0, $sp, 8		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		la $a0 _L0		# load a0 with the string address
		li $v0 4		# prepare for the syscall to print string
		syscall		# print the string
				
		la $a0 _NL		# load with a newline character
		li $v0 4		# prepare to print new line
		syscall		# system call to print newline
				
				
		lw $ra, 4($sp)		 #restore RA
		lw $sp, ($sp)		 #restore SP
				
		li $v0, 10		# leave MAIN program
		syscall		# Leave MAIN

.data
struct:	.space 1170
								;data 12 - nome 15 - km 4 - qnt 4 - prc 4 = total 39
								;0 - day | 4 - month | 8 - year | 12 - name | 27 - 

.globl main

.text

main:
	la $s0, struct

	addi $v0, $zero, 5
	syscall 					;input day
	sw $v0, 0($s0)
	
	addi $v0, $zero, 5
	syscall 					;input month
	sw $v0, 4($s0)
	
	addi $v0, $zero, 5
	syscall 					;input year
	sw $v0, 8($s0)

	la $a0, 12($s0)				;Delimitação do limite da string
	addi $a1, $zero, 15
	
	addi $v0, $zero, 8
	syscall						;input name
	

	
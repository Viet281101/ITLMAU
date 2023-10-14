.text
.globl main

countdown:
	add $sp, $sp, -4
	sw $ra, 0($sp)

	beq $a0, $zero, cd_else
	li $v0, 1
	syscall
	move $t0, $a0
	li $v0, 4
	la $a0, nl
	syscall

	add $a0, $t0, -1
	jal countdown
	b cd_end

cd_else:
	li $v0, 4
	la $a0, boum
	syscall

	lw $ra, 0($sp)
	add $sp, $sp, 4
	jr $ra

main:
	add $sp, $sp, -4
	sw $ra, 0($sp)

	li $v0, 4
	la $a0, cf
	syscall

	li $v0, 5
	syscall
	move $t0, $v0, # t0 is n

	move $a0, $t0
	jal countdown

	li $v0, 0
	lw $ra, 0($sp)
	add $sp, $sp, 4
	jr $ra


.data
nl: .asciiz "\n"
boum: .asciiz "BOUM!\n"
cf: .asciiz "Count from? \t"

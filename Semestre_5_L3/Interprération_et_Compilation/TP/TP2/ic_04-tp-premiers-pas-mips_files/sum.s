.data
prompt:     .asciiz "Enter a positive integer (n): "
result_msg: .asciiz "The sum of the first n integers is: "
nl:         .asciiz "\n"

.text
.globl main

main:
    li $v0, 4
    la $a0, prompt
    syscall

    li $v0, 5
    syscall
    move $t0, $v0

    bgtz $t0, calculate_sum
    li $v0, 4
    la $a0, nl
    syscall
    j end_program

calculate_sum:
    li $t1, 0
    li $t2, 1

sum_loop:
    beq $t2, $t0, print_result

    add $t1, $t1, $t2

    addi $t2, $t2, 1

    j sum_loop

print_result:
    li $v0, 4
    la $a0, result_msg
    syscall

    move $a0, $t1
    li $v0, 1
    syscall

end_program:
    li $v0, 10
    syscall

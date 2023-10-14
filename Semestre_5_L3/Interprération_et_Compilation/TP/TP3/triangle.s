
.text
.globl main

main:
    li $t0, 1
    li $t1, 1

outer_loop:
    beq $t0, 32, done

    inner_loop:
        beq $t1, $t0, print_newline

        li $v0, 11
        li $a0, '#'
        syscall

        addi $t1, $t1, 1
        j inner_loop

    print_newline:
        li $v0, 11
        li $a0, 10
        syscall

        addi $t0, $t0, 1
        li $t1, 1
        j outer_loop

done:
    li $v0, 10
    syscall

.data

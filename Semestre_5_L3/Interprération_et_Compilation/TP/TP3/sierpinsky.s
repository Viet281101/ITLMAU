.text
.globl main

main:
    li $t0, 1
    li $t1, 1
    li $t2, 1

outer_loop:
    beq $t0, 32, done

    inner_loop:
        beq $t1, $t0, print_space_or_hash

        beq $t2, 1, print_hash
        j print_space

    print_space_or_hash:
        beq $t1, $t0, print_newline
        j toggle_space_or_hash

    print_hash:
        li $v0, 11
        li $a0, '#'
        syscall
        j toggle_space_or_hash

    toggle_space_or_hash:
        xori $t2, $t2, 1
        addi $t1, $t1, 1
        j inner_loop

    print_space:
        li $v0, 11
        li $a0, ' '
        syscall
        j toggle_space_or_hash

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
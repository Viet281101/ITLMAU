
.text
.globl main

main:
    li $t0, 1                  # x
    li $t1, 2147483648         # 2**31 (limit for x)

loop_x:

    bgtu $t0, $t1 , end_loop_x #if x < 10

    move $t2, $t0              # n

loop_n:
    blez $t2, end_loop_n       # if n < 0

    li $t3, 1
    and $t4, $t2, $t3          # $t3 = x & 1 ($t3 == 1 --> x impair)

    beq $t4, $zero, x_odd_false
x_odd_true:
    # print "#"
    li $v0, 4
    la $a0, diez
    syscall

    j end_if
x_odd_false:
    # print " "
    li $v0, 4
    la $a0, space
    syscall
end_if:
    srl $t2, $t2, 1      # n = n >> 1

    j loop_n

end_loop_n:
    # print "\n"
    li $v0, 4
    la $a0, nl
    syscall

    # x ^= x << 1
    sll $t3, $t0, 1      # $t3 = x << 1
    xor $t0, $t0, $t3    # x = x ^ $t3

    j loop_x
end_loop_x:

    li $v0, 4
    la $a0, aled
    syscall

    jr $ra


.data
nl: .asciiz "\n"
space: .asciiz " "
diez: .asciiz "#"
aled: .asciiz "bye\n"
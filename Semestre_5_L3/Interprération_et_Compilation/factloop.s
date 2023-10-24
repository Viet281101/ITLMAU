
factloop_hw:
    lw $t0, 0($sp) # t0 is n
    li $t1, 1 # t1 is r

flwh_loop:
    blez $t0, flwh_endloop # if n <= 0, end
    mul $t1, $t1, $t0 # r = r * n
    addi $t0, $t0, -1 # n = n - 1
    b flwh_loop

flwh_endloop:
    move $v0, $t1 # return r
    jr $ra


######################

factloop:
    addi $sp, $sp, -12 # push
    sw $ra, 8($sp) # save return address
    sw $fp, 4($sp) # save n
    addi $fp, $sp, 4 # set up new frame pointer

    li $v0, 1 # read n
    sw $v0, 0($fp) # r =

loop001:
    lw $v0, 12($fp) # load n
    addi $sp, $sp, -4 # push
    sw $v0, 0($sp) # push n
    li $v0, 0 # read n
    addi $sp, $sp, -4 # push
    sw $v0, 0($sp) # push n
    jal __gt
    addi $sp, $sp, 8 # pop n and 0
    beqz $v0, endloop001 # if n <= 0, end
    lw $v0, 12($fp) # load n
    addi $sp, $sp, -4 # push
    sw $v0, 0($sp) # push n
    lw $v0, 0($f p) # r
    addi $sp, $sp, -4 # push
    sw $v0, 0($sp) # push r
    jal __mul
    addi $sp, $sp, 8 # pop r and n
    sw $v0, 0($fp) # r = r * n
    lw $v0, 12($fp) # load n
    addi $sp, $sp, -4 # push
    sw $v0, 0($sp) # push n
    li $v0, 1 # read n
    addi $sp, $sp, -4 # push
    sw $v0, 0($sp) # push n
    li $v0, 1 # read n
    jal __sub
    addi $sp, $sp, 8 # pop n and 1
    sw $v0, 12($fp) # n = n - 1
    b loop001

endloop001:
    lw $v0, 0($fp) # load r
    
    lw $ra, 8($fp) # restore return address
    lw $fp, 4($fp) # restore frame pointer
    addi $sp, $sp, 12 # pop

    jr $ra

######################



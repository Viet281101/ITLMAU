.text
.globl main
_add:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  add $v0, $t0, $t1
  jr $ra
_sub:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  sub $v0, $t1, $t0
  jr $ra
_mul:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  mul $v0, $t0, $t1
  jr $ra
_div:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  div $v0, $t1, $t0
  jr $ra
_equal:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  seq $v0, $t1, $t0
  jr $ra
_nequal:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  sne $v0, $t1, $t0
  jr $ra
_gt:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  sgt $v0, $t1, $t0
  jr $ra
_gte:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  sge $v0, $t1, $t0
  jr $ra
_lt:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  slt $v0, $t1, $t0
  jr $ra
_lte:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  sle $v0, $t1, $t0
  jr $ra
_or:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  or $v0, $t1, $t0
  jr $ra
_and:
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  and $v0, $t1, $t0
  jr $ra
puti:
  lw $a0, 0($sp)
  li $v0, 1
  syscall
  jr $ra
geti:
  lw $a0, 0($sp)
  li $v0, 5
  syscall
  jr $ra
puts:
  lw $a0, 0($sp)
  li $v0, 4
  syscall
  jr $ra
gets:
  lw $a0, 0($sp)
  li $v0, 8
  syscall
  jr $ra
main:
  addi $sp, $sp, -16
  sw $ra, 12($sp)
  sw $fp, 8($sp)
  addi $fp, $sp, 12
  la $v0, str0
  sw $v0, 8($fp)
  lw $v0, 8($fp)
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  jal puts
  addi $sp, $sp, 4
  jal gets
  addi $sp, $sp, 0
  sw $v0, 12($fp)
  lw $v0, 12($fp)
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  jal puts
  addi $sp, $sp, 4
  addi $sp, $sp, 16
  lw $ra, 0($fp)
  lw $fp, -4($fp)
  jr $ra
  move $a0, $v0
  li $v0, 1
  syscall
  addi $fp, $sp, -4
 jr $ra

.data
str0: .asciiz "Bonjour"

.text
.globl main

main:
  li $v0, 4   ### définir le code de la fonction
  la $a0, hw  ### initialiser les arguments
  syscall
  jr $ra

.data
hw: .asciiz "Hello, world!\n"

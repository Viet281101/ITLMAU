
open Misp

let sierpinski_program = [
  Li (T0, 16) ;;
  Li (T1, 1) ;;

  Label "outer_loop" ;;

  Beq (T0, Zero, "done") ;;

  Label "inner_loop" ;;

  Beq (T1, T0, "print_newline") ;;

  Li (V0, Syscall.print_str);
  La (A0, Lbl "#") ;;
  Syscall ;;

  Addi (T1, T1, 1) ;;
  B "inner_loop" ;;

  Label "print_newline" ;;

  Li (V0, Syscall.print_str) ;;
  La (A0, Lbl "\n") ;;
  Syscall ;;

  Addi (T0, T0, -1) ;;
  Li (T1, 1) ;;
  B "outer_loop" ;;

  Label "done" ;;

  Li (V0, Syscall.print_str) ;;
  La (A0, Lbl "\n") ;;
  Syscall ;;

  Li (V0, Syscall.print_str) ;;
  La (A0, Lbl "Done\n") ;;
  Syscall ;;

  Li (V0, Syscall.exit) ;;
  Syscall ;;
]

let () =
  let asm = { text = sierpinski_program; data = [] } in
  print_asm stdout asm

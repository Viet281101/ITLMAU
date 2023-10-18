
open Mips
open Mips_helper


let () =
  print_asm Stdlib.stdout
    {
      text =
        def "main"
          ( [ Li (T0, 1) ]
          @ (loop(LessThanEqual  (T0, 2147483648))
            
            ( [Move (T1, T0) ]
            @ (loop (GreaterThan (T1, 0))
              ( [ Andi (T2, T1, 1) ]
              @ (branch (NotEqual (T2, Zero))
                  (print_str "sharp")
                  (print_str "space")
                )
              @ [ Srl (T1, T1, 1) ]
              )
              )
            @ (print_str "nl")
            @ [Sll (T2, T0, 1)
              ; Xor (T0, T0, T2) ]
            )
            )
          )
      ; data = [
        ("nl", Asciiz "\\n")
        ; ("sharp", Asciiz "#")
        ; ("space", Asciiz " ")
      ]
    }


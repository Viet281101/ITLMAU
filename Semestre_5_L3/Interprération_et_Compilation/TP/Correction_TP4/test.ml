
open Ast

let () = 
  let prog = [
    Assign ("x", Value (Int 21))
  ; Assign ("truc", Call ("%add", [Var "x" ; Value (Int 3) ]))
  ; Assign ("y", Call ("%mul", [Value (Int 2) ; Value "truc"]))
  ; Return (Var "y")
  ]
in 
Print.print_value (Interp.eval prog) ;
print_newline ()


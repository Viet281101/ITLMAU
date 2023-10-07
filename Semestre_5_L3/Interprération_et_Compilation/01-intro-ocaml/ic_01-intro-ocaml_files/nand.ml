open Ast.Nand
open Ast.Byte

let rec compile = function
  | B false  -> [ False ]
  | B true   -> [ True ]
  | N (a, b) -> (compile a) @ [ Push ] @ (compile b) @ [ Hold ; Pop ; Nand ]

(* bonus: eval, useless in our compiler except to make some tests *)
let rec eval = function
  | B e      -> e
  | N (a, b) -> not ((eval a) && (eval b))

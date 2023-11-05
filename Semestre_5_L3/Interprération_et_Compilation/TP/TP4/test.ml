
open Ast.IR
open Interp
open Print



let () = 
  let code = Str "Hello, World!"
  in print_const (eval_const code)



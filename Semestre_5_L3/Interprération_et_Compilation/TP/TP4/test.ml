

open Ast.IR
open Interp
open Print



(* let () = 
  let code = Str "Hello, World!"
  in print_const (eval_const code) *)


let () = 
  let defs = [
    Func ("%main", [], [
      Assign ("res", Call ("%add", [Value (Int 3); Value (Int 4)]));
      Return (Var "res")
    ])
  ] in
  let main_block = 
    match List.find (fun def -> match def with Func (name, _, _) -> name = "%main" | _ -> false) defs with
    | Func (_, _, block) -> block
    | _ -> failwith "%main function not found"
  in
  let result = eval main_block in
  print_const result


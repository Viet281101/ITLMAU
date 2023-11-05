

open Ast.IR
open Interp
open Print
open Sierpinsky_ir


(* let () = 
  let code = Str "Hello, World!"
  in print_const (eval_const code) *)


let () = 
  let defs = [
    Func ("%main", [], [
      Assign ("res", Call ("puti", [Value (Int 42)]));
      Return (Var "res")
    ])
  ] in
  let main_block = 
    match List.find_opt (fun def -> match def with Func (name, _, _) -> name = "%main") defs with
    | Some (Func (_, _, block)) -> block
    | None -> failwith "%main function not found"
  in
  let result = eval main_block in
  print_const result

(* let () = 
  let main_block = 
    match List.find_opt (fun def -> match def with Func (name, _, _) -> name = "main") prog with
    | Some (Func (_, _, block)) -> block
    | None -> failwith "main function not found"
  in
  let _result = eval main_block in
  () *)

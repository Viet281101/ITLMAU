open Ast
open Ast.IR
open Baselib

exception Error of string * Lexing.position

(* fonctions d'aide à la gestion des erreurs *)

let expr_pos expr =
  match expr with
  | Syntax.Value v -> v.pos
  | Syntax.Var v   -> v.pos
  | Syntax.Call c  -> c.pos

let errt expected given pos =
  raise (Error (Printf.sprintf "expected %s but given %s"
                  (string_of_type_t expected)
                  (string_of_type_t given),
                pos))

(* analyse sémantique *)

let env = ref Env.empty

let analyze_value value =
  match value with
  | Syntax.Bool b -> Bool b
  | Syntax.Int n  -> Int n

let rec analyze_expr expr =
  match expr with
  | Syntax.Value v ->
     Value (analyze_value v.value)
  | Syntax.Var v ->
     Var v.name
  | Syntax.Call c ->
     let args = List.map analyze_expr c.args in
     Call (c.func, args)

let analyze_instr instr =
  match instr with
  | Syntax.Decl d ->
     env := Env.add d.name () !env;
     Decl d.name
  | Syntax.Assign a ->
     let ae = analyze_expr a.expr in
     if Env.mem a.var !env then
       Assign (a.var, ae)
     else
       raise (Error ("unbound variable: " ^ a.var, expr_pos a.expr))

let rec analyze_block block =
  match block with
  | [] -> []
  | instr :: rest ->
     let ai = analyze_instr instr in
     ai :: (analyze_block rest)

let analyze parsed =
  analyze_block parsed
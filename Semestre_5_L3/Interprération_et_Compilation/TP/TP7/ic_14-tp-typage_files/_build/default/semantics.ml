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

let analyze_value value =
  match value with
  | Syntax.Bool b -> Bool b, Bool_t
  | Syntax.Int n  -> Int n, Int_t

let rec analyze_expr expr =
  match expr with(* Decl d.name *)
  | Syntax.Value v ->
     Value (analyze_value v.value)
  | Syntax.Var v ->
     Var v.name
  | Syntax.Call c ->
     let args = List.map analyze_expr c.args in
     Call (c.func, args)

let analyze_instr instr env =
  match instr with
  | Syntax.Decl d ->
     (* Decl d.name *)
     (* compléter en ajoutant la variables déclarée *)
     Decl d.name, Env.add d.name, d.type_t , env
  | Syntax.Assign a ->
      (* vérification que a.var existe ? *)
      if Env.mem a.var env then
        let ae, et = analyze_expr a.expr env in
        let vt = Env.find a.var env in
        if vt = et then 
          Assign (a.var, ae), env
        else
          errt vt et (expr.pos a.expr)
      else
        raise (Error (Printf.sprintf "unbound variable '%s'" a.var, a.pos) )
     (* let ae = analyze_expr a.expr in
     Assign (a.var, ae) *)

let rec analyze_block block env =
  match block with
  | [] -> []
  | instr :: rest ->
     let ai, new_env = analyze_instr instr env in
     ai :: (analyze_block rest new_env)

let analyze parsed =
  analyze_block parsed Baselib._types_

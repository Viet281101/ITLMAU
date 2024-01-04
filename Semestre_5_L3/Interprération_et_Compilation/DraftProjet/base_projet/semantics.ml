open Ast
open Baselib

exception Error of string * Lexing.position

let analyze_value value =
  match value with
  | Syntax.Void -> V1.Void
  | Syntax.Bol b -> V1.Bol b
  | Syntax.Int n -> V1.Int n
  | Syntax.Str s -> V1.Str s
let analyze_expr expr _ =
  match expr with
  | Syntax.Val v -> IR1.Val (analyze_value v.value)

let analyze parsed =
  analyze_expr parsed Baselib._types_

let collect_constant_strings code =
  let counter = ref (-1) in
  let ccs_value v env =
    match v with
    | V1.Void   -> (V2.Void, env)
    | V1.Bol b -> (V2.Bol b, env)
    | V1.Int n -> (V2.Int n, env)
    | V1.Str s -> (
        ( V2.Dat s,
          match Env.find_opt s env with
          | Some _ -> env
          | None   -> incr counter; Env.add s ("str" ^ string_of_int !counter) env ))
  in
  let ccs_expr e env =
    match e with
    | IR1.Val v ->
        let v, ccs = ccs_value v env in
        (IR2.Val v, ccs)
  in
  ccs_expr code Baselib.label
  
let simplify code = collect_constant_strings code

let analyze_statement st env = match st with
| Syntax.VarDecl vd ->
    let analyzed_vinit = analyze_expr vd.vinit env in
    (IR1.VarDecl { vname = vd.vname; vtype = analyze_value vd.vtype; vinit = analyzed_vinit }, env)
| Syntax.Print e ->
    let analyzed_expr = analyze_expr e env in
    (IR1.Print analyzed_expr, env)

let analyze_expr expr env = match expr with
  | Syntax.Val v -> IR1.Val (analyze_value v.value)
  | Syntax.Var vname -> IR1.Var (Env.find vname env)
  | Syntax.Stmt s -> analyze_statement s env

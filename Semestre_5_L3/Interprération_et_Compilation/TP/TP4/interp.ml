

open Ast.IR
open Baselib.Env

type 'a result =
  | Ret of value
  | Env of 'a t

let eval_const = function
  | Nil -> Nil
  | Bool b -> Bool b
  | Int n -> Int n
  | Str s -> Str s

let rec eval_expr e env = 
  match e with
  | Value v -> eval_const v
  | Var v -> find v env
  | Call (f, args) ->
      failwith "Function call evaluation not yet implemented"

let rec eval_instr i env = 
  match i with
  | Return e -> Ret (eval_expr e env)
  | Expr e -> 
      let _ = eval_expr e env in Env env
  | Assign (v, e) -> Env(add v (eval_expr e env) env)
  | Cond (cond, then_block, else_block) ->
      let result = eval_expr cond env in
      begin
        match result with
        | Bool true -> eval_block then_block env
        | Bool false -> eval_block else_block env
        | _ -> failwith "Condition must be a boolean"
      end
  | Loop (cond, block) ->
      failwith "Loop evaluation not yet implemented"

and eval_block b env = 
  match b with
  | [] -> Env env
  | i :: r ->
    match eval_instr i env with
    | Ret v -> Ret v
    | Env e -> eval_block r e

let eval prog =
  match eval_block prog empty with
  | Ret v -> v
  | Env _ -> Nil
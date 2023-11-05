

open Ast.IR
open Baselib

type 'a result =
  | Ret of value
  | Env of 'a Env.t

let eval_const = function
  | Nil -> Nil
  | Bool b -> Bool b
  | Int n -> Int n
  | Str s -> Str s

let eval_native (func: native) args =
  func args

let rec eval_expr e env =
  match e with
  | Value v -> eval_const v
  | Var v ->
    (match Env.find_opt v env with
    | Some (V value) -> value
    | Some (N _) | Some (F _) | None -> failwith "Expected value, found function or function not found")
  | Call (f, arg_exprs) ->
    let func = match Env.find_opt f env with
      | Some (N native_func) -> native_func
      | Some (V _) | Some (F _) | None -> failwith "Expected function, found value or function not found"
    in
    let arg_values = List.map (fun arg -> eval_expr arg env) arg_exprs in
    eval_native func arg_values

and eval_instr i env =
  match i with
  | Return e -> Ret (eval_expr e env)
  | Expr e -> let _ = eval_expr e env in Env env
  | Assign (v, e) -> Env(Env.add v (V (eval_expr e env)) env)
  | Cond (cond, then_block, else_block) ->
    let result = eval_expr cond env in
    begin
      match result with
      | Bool true -> eval_block then_block env
      | Bool false -> eval_block else_block env
      | _ -> failwith "Condition must be a boolean"
    end
  | Loop (cond, block) ->
    let rec loop env =
      match eval_expr cond env with
      | Bool true -> (match eval_block block env with
                      | Env env' -> loop env'
                      | Ret v -> Ret v)
      | Bool false -> Env env
      | _ -> failwith "Loop condition must be a boolean"
    in loop env

and eval_block b env =
  match b with
  | [] -> Env env
  | i :: r ->
    match eval_instr i env with
    | Ret v -> Ret v
    | Env e -> eval_block r e

let eval prog =
  match eval_block prog Baselib.baselib with
  | Ret v -> v
  | Env _ -> Nil


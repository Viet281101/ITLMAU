
open Ast
open Baselib

let eval_value (v : value) = v

let rec eval_expr env = function 
  | Value v -> eval_value v
  | Var n ->
    (match Env.find n env with
    | V v -> v
    | _ -> failwith "Should not happen")
  | Call (f, a) -> 
    (match Env.find f env with
    | N f -> f (List.map (eval_expr env) a)
    | _ -> failwith "Should not happen")


type 'a res = 
  | Stop of value
  | Cont of 'a Env.t


let eval_instr env = function
  | Return e -> Stop (eval_expr env e)
  | Assign (v, e) -> Cont (Env.add v (eval_expr env e ) env)


let eval_block env = function
  | [] -> Cont env 
  | i :: b -> 
    match eval_instr env i with 
    | Stop v -> Stop v
    | Cont e -> eval_block e b

let eval prog =
  match eval_block Baselib Env.empty prog with
  | Stop v -> v
  | Cont _ -> Void


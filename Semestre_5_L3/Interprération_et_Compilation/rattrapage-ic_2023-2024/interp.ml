open Ast.IR
open Baselib

let eval_value (v : value) = v

let rec eval_expr env = function
  | Val v -> eval_value v
  | Var v ->
    (match Env.find v env with
     | V v -> eval_value v
     | _ -> failwith "Should not happen")
  | Cal (f, a) ->
    (match Env.find f env with
     | N f -> f (List.map (eval_expr env) a)
     | _ -> failwith "Should not happen")

type 'a res =
| Stop of value
| Cont of 'a Env.t

let eval_instr env = function
  | Return e -> Stop (eval_expr env e)
  | Assign (v, e) -> Cont (Env.add v (V (eval_expr env e)) env)

let rec eval_block env = function
  | [] -> Cont env
  | i :: b ->
    match eval_instr env i with
    | Stop v -> Stop v
    | Cont e -> eval_block e b

let eval prog =
  match eval_block Baselib._stdlib_ prog with
  | Stop v -> v
  | Cont _ -> Nil

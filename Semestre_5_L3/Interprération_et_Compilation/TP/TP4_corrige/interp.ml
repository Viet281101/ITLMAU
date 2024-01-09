open Ast
open Baselib

let eval_value v = v

let rec eval_expr (expression) (env) =
  match expression with
  | Var_value valeur -> eval_value valeur
  | Var_name chaine ->  (match Env.find chaine env with
    | V v -> v
    | _ -> failwith "returning a function")
  | Call (id, args) -> (match Env.find id env with
    | N id -> id (List.map (fun expr -> eval_expr expression env) args) 
    | _ -> failwith "should not happen")


let eval_instr instr env =
  match instr with
  | Return expr -> Ret (eval_expr expr env)
  | Assign (nom, expr) -> Env (Env.add nom (V(eval_expr expr env)) env)
  


let rec eval_block bloc env =
  match bloc with
  | [] -> Env env
  | top::rest -> match (eval_instr top env) with
    | Ret valeur -> Ret valeur
    | Env lenv -> eval_block rest lenv


let eval prog =
  match eval_block prog Env.empty with
  | Ret v -> v
  | Env e -> Void



open Ast.IR

module Env = Map.Make(String)

type native = value list -> value

type env_value =
  | V of value
  | N of native
  | F of string list * block

type env = env_value Env.t

let empty_env : env = Env.empty

let eq_fun args =
  match args with
  | [Int a; Int b] -> Bool (a = b)
  | _ -> failwith "eq function expects two integers"

let lt_fun args =
  match args with
  | [Int a; Int b] -> Bool (a < b)
  | _ -> failwith "lt function expects two integers"

let gt_fun args =
  match args with
  | [Int a; Int b] -> Bool (a > b)
  | _ -> failwith "gt function expects two integers"

let geti_fun _args =
  let input = read_line () in
  Int (int_of_string input)

let puti_fun args =
  match args with
  | [Int a] -> print_int a; print_newline (); Nil
  | _ -> failwith "puti function expects one integer"

let puts_fun args =
  match args with
  | [Str s] -> print_string s; print_newline (); Nil
  | _ -> failwith "puts function expects one string"

let rand_fun args =
  match args with
  | [Int upper] -> Int (Random.int upper)
  | _ -> failwith "rand function expects one integer as upper bound"

let baselib : env =
  let open Env in 
  empty
  |> add "eq" (N eq_fun)
  |> add "lt" (N lt_fun)
  |> add "gt" (N gt_fun)
  |> add "geti" (N geti_fun)
  |> add "puti" (N puti_fun)
  |> add "puts" (N puts_fun)
  |> add "rand" (N rand_fun)


let () = Random.self_init ()


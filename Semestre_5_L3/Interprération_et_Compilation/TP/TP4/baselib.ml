

open Ast.IR

type native = value list -> value

type env_value =
  | V of value
  | N of native

module Env = Map.Make(String)

let add_native_fun name func env =
  Env.add name (N func) env

let baselib =
  let open Env in
  empty
  |> add_native_fun "%add" (function
    | [Int a; Int b] -> Int (a + b)
    | _ -> failwith "add function expects two integers")



(* let baselib = Env.add "%add"
  (N (function [ Int a ; Int b ] -> Int (a + b)
    | _ -> failwith "ERROR")) (* should never happen *)
  Env.empty *)

(* module Env = Map.Make(struct 
  type t = string
  let compare = compare
end) *)

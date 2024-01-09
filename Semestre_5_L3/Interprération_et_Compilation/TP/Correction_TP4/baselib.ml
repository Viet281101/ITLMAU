
open Ast

module Env = Map.Make(String)

type native = value list -> value

type env_value = 
  | V of value
  | N of native

let baselib = 
  List.fold_left (fun env (name, func) -> Env.add name func env)
  Env.empty

  [ (Env.add "%mul"
      (N (function [Int a ; Int b] -> Int (a * b) 
        | _ -> failwith "Should not happen!")))

  ; (Env.add "%add" 
      (N (function [ Int a ; Int b ] -> Int (a + b) 
        | _ -> failwith "Should not happen!")))
  
  ; (Env.add "%sub" 
      (N (function [ Int a ; Int b ] -> Int (a - b) 
        | _ -> failwith "Should not happen!")))

  ; (Env.add "%div" 
      (N (function [ Int a ; Int b ] -> Int (a / b) 
        | _ -> failwith "Should not happen!")))
  ; ("True", V (Bool true))
  ; ("False", V (Bool false))
]


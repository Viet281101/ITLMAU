open Baselib


type value =
  | Void
  | Bool of bool 
  | Int of int 
  | Str of string


type native = value list -> value

type expr = 
  | Var_value of value
  | Var_name of string
  | Call of string * expr list

type instr = 
  | Return of expr
  | Assign of string * expr
and block = instr list



type 'a res =
  | Ret of value
  | Env of 'a Env.t



type env_value =
  | V of value
  | N of native


let bl_add = function
| [Int a; Int b] -> Int(a+b)
| _ -> failwith "error"

let bl_mul = function
| [Int a; Int b] -> Int(a*b)
| _ -> failwith "error"


let baselib = Env.add "%add" (N bl_add) Env.empty
let baselib = Env.add "%add" (N bl_mul) baselib


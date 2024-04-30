open Ast
open Ast.IR

module Env = Map.Make(String)

let _types_ =
	Env.of_seq
		(List.to_seq
			[ "%add", Func_t (Int_t, [ Int_t ; Int_t ])
			; "%sub", Func_t (Int_t, [ Int_t ; Int_t ])
			; "%mul", Func_t (Int_t, [ Int_t ; Int_t ])
			; "%div", Func_t (Int_t, [ Int_t ; Int_t ])
		])

type env_value =
| V of value
| N of (value list -> value)

let _stdlib_ =
	Env.of_seq
		(List.to_seq
			[ ("%add", N (function [ Int a ; Int b ] -> Int (a + b)
													 | _ -> failwith "Should not happen!"))
			; ("%sub", N (function [ Int a ; Int b ] -> Int (a - b)
													 | _ -> failwith "Should not happen!"))
			; ("%mul", N (function [ Int a ; Int b ] -> Int (a * b)
													 | _ -> failwith "Should not happen!"))
			; ("%div", N (function [ Int a ; Int b ] -> Int (a / b)
													 | _ -> failwith "Should not happen!"))
			])

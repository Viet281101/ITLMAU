open Ast.IR

let fmt_value = function
	| Nil -> Printf.sprintf "nil"
	| Int n -> Printf.sprintf "%d" n
	| Bool b -> Printf.sprintf "%b" b

let print_value v = Printf.printf "%s" (fmt_value v)

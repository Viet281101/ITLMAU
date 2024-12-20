type type_t =
	| Int_t
	| Func_t of type_t * type_t list
	| Bool_t

let rec string_of_type_t t =
	match t with
	| Int_t  -> "int"
	| Func_t (r, a) ->
		 (if (List.length a) > 1 then "(" else "")
		 ^ (String.concat ", " (List.map string_of_type_t a))
		 ^ (if (List.length a) > 1 then ")" else "")
		 ^ " -> " ^ (string_of_type_t r)
	| Bool_t -> "bool"

module Syntax = struct
	type value =
	| Int of int
	| Bool of bool

	type ident = string

	type expr =
	| Val of { value: value
					 ; pos: Lexing.position }
	| Var of { name: ident
					 ; pos: Lexing.position }
	| Cal of { func: ident
					 ; args: expr list
					 ; pos: Lexing.position }
	| If of { condition: expr
					 ; then_branch: expr
					 ; else_branch: expr
					 ; pos: Lexing.position }

	type instr =
	| Assign of { var: ident
							; expr: expr
							; pos: Lexing.position }
	| Return of { expr: expr
							; pos: Lexing.position }
	and block = instr list
end

module IR = struct
	type value =
	| Nil
	| Int of int
	| Bool of bool

	type ident = string

	type expr =
	| Val of value
	| Var of ident
	| Cal of ident * expr list
	| If of expr * expr * expr

	type instr =
	| Return of expr
	| Assign of ident * expr
	and block = instr list
end

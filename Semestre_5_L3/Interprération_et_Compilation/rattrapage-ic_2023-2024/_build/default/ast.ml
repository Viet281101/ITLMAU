type type_t =
	| Int_t
	| Func_t of type_t * type_t list

let rec string_of_type_t t =
	match t with
	| Int_t  -> "int"
	| Func_t (r, a) ->
		 (if (List.length a) > 1 then "(" else "")
		 ^ (String.concat ", " (List.map string_of_type_t a))
		 ^ (if (List.length a) > 1 then ")" else "")
		 ^ " -> " ^ (string_of_type_t r)

module Syntax = struct
	type value =
	| Int of int

	type ident = string

	type expr =
	| Val of { value: value
					 ; pos: Lexing.position }
	| Var of { name: ident
					 ; pos: Lexing.position }
	| Cal of { func: ident
					 ; args: expr list
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

	type ident = string

	type expr =
	| Val of value
	| Var of ident
	| Cal of ident * expr list

	type instr =
	| Return of expr
	| Assign of ident * expr
	and block = instr list
end

open Ast
open Ast.IR
open Baselib

exception Error of string * Lexing.position

(* fonctions d'aide à la gestion des erreurs *)

let expr_pos expr =
	match expr with
	| Syntax.Val v -> v.pos
	| Syntax.Var v -> v.pos
	| Syntax.Cal c -> c.pos
	| Syntax.If { condition; pos; _ } -> pos

let errt expected given pos =
	raise (Error (Printf.sprintf "expected %s but given %s"
									(string_of_type_t expected)
									(string_of_type_t given),
								pos))

(* analyse sémantique *)

let analyze_value = function
	| Syntax.Int n -> Int n, Int_t
	| Syntax.Bool b -> Bool b, Bool_t

let rec analyze_expr expr env =
	match expr with
	| Syntax.Val v ->
		let av, vt = analyze_value v.value in
		Val av, vt
	| Syntax.Var v ->
		if Env.mem v.name env then
			Var v.name, Env.find v.name env
		else
			raise (Error (Printf.sprintf "unbound variable '%s'" v.name,
										v.pos))
	| Syntax.Cal c -> begin
			match Env.find_opt c.func env with
			| Some (Func_t (rt, at)) ->
				if List.length at != List.length c.args then
					raise (Error (Printf.sprintf "expected %d arguments but given %d"
												 (List.length at) (List.length c.args), c.pos)) ;
				let args = List.map2 (fun eat a -> let aa, at = analyze_expr a env
																					 in if at = eat then aa
																							else errt eat at (expr_pos a))
										 at c.args in
				Cal (c.func, args), rt
			| Some _ -> raise (Error (Printf.sprintf "'%s' is not a function" c.func,
																c.pos))
			| None -> raise (Error (Printf.sprintf "undefined function '%s'" c.func,
															c.pos))
		end
	| Syntax.If { condition; then_branch; else_branch; pos } ->
		let cond_val, cond_type = analyze_expr condition env in
		if cond_type != Bool_t then
				raise (Error ("condition must be a boolean expression", pos));
		let then_val, _ = analyze_expr then_branch env in
		let else_val, _ = analyze_expr else_branch env in
		IR.If (cond_val, then_val, else_val), Int_t

let analyze_instr instr env =
	match instr with
	| Syntax.Assign a ->
		let ae, et = analyze_expr a.expr env in
		Assign (a.var, ae), Env.add a.var et env
	| Syntax.Return r ->
		let ae, _ = analyze_expr r.expr env in
		Return ae, env

let rec analyze_block block env =
	match block with
	| [] -> []
	| instr :: rest ->
		let ai, new_env = analyze_instr instr env in
		ai :: (analyze_block rest new_env)

let analyze parsed =
	analyze_block parsed Baselib._types_

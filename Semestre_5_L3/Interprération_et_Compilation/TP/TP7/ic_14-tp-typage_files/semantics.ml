open Ast
open Ast.IR
open Baselib

exception Error of string * Lexing.position

(* fonctions d'aide à la gestion des erreurs *)

let expr_pos expr =
  match expr with
  | Syntax.Value v -> v.pos
  | Syntax.Var v   -> v.pos
  | Syntax.Call c  -> c.pos

let errt expected given pos =
  raise (Error (Printf.sprintf "expected %s but given %s"
                  (string_of_type_t expected)
                  (string_of_type_t given),
                pos))

(* analyse sémantique *)

let initialize_env () =
  let initial_env = Env.empty in
  let add_func name typ env = Env.add name typ env in
  let env_with_funcs = List.fold_right (fun (name, typ) env ->
    add_func name typ env) 
    [ ("%add", Func_t (Int_t, [ Int_t ; Int_t ]))
    ; ("%sub", Func_t (Int_t, [ Int_t ; Int_t ]))
    ; ("%mul", Func_t (Int_t, [ Int_t ; Int_t ]))
    ; ("%div", Func_t (Int_t, [ Int_t ; Int_t ]))
    ; ("%eq",  Func_t (Bool_t, [ Int_t ; Int_t ]))
    ; ("%neq", Func_t (Bool_t, [ Int_t ; Int_t ]))
    ; ("%lt",  Func_t (Bool_t, [ Int_t ; Int_t ]))
    ; ("%gt",  Func_t (Bool_t, [ Int_t ; Int_t ]))
    ; ("%lte", Func_t (Bool_t, [ Int_t ; Int_t ]))
    ; ("%gte", Func_t (Bool_t, [ Int_t ; Int_t ]))
    ] initial_env in
  env_with_funcs

let env = ref (initialize_env ())
let assigned = ref Env.empty

let check_type expected actual pos =
  if expected <> actual then
    errt expected actual pos

let analyze_value value =
  match value with
  | Syntax.Bool b -> Bool_t, Bool b
  | Syntax.Int n  -> Int_t, Int n

let rec analyze_expr expr =
  match expr with
  | Syntax.Value v ->
     let typ, val' = analyze_value v.value in
     typ, Value val'
  | Syntax.Var v ->
    if Env.mem v.name !env then
      let typ = Env.find v.name !env in
      if Env.mem v.name !assigned && not (Env.find v.name !assigned) then
        Printf.eprintf "Warning on line %d col %d: Unassigned variable '%s'.\n"
          v.pos.pos_lnum (v.pos.pos_cnum - v.pos.pos_bol) v.name;
      typ, Var v.name
    else
      raise (Error ("Unbound variable: " ^ v.name, v.pos))
  | Syntax.Call c ->
    if Env.mem c.func !env then
      let arg_types, args = List.fold_right (fun arg (typs, aexprs) ->
        let atyp, aexpr = analyze_expr arg in
        (atyp :: typs, aexpr :: aexprs)) c.args ([], [])
      in
      let func_typ = Env.find c.func !env in
      (match func_typ with
       | Func_t (ret_typ, param_types) ->
          if List.length param_types <> List.length arg_types then
            raise (Error (Printf.sprintf "Incorrect number of arguments for %s" c.func, c.pos))
          else
            List.iter2 (fun expected actual ->
              check_type expected actual c.pos) param_types arg_types;
          ret_typ, Call (c.func, args)
       | _ -> raise (Error ("Function type expected for " ^ c.func, c.pos)))
    else
      raise (Error ("Unbound function: " ^ c.func, c.pos))

let analyze_instr instr =
  match instr with
  | Syntax.Decl d ->
     env := Env.add d.name d.type_t !env;
     assigned := Env.add d.name false !assigned;
     Decl d.name
  | Syntax.Assign a ->
    if Env.mem a.var !env then
      let expected_typ = Env.find a.var !env in
      let actual_typ, ae = analyze_expr a.expr in
      check_type expected_typ actual_typ (expr_pos a.expr);
      assigned := Env.add a.var true !assigned;
      Assign (a.var, ae)
    else
      raise (Error ("Unbound variable: " ^ a.var, expr_pos a.expr))

let rec analyze_block block =
  match block with
  | [] -> []
  | instr :: rest ->
     let ai = analyze_instr instr in
     ai :: (analyze_block rest)

let analyze parsed =
  analyze_block parsed


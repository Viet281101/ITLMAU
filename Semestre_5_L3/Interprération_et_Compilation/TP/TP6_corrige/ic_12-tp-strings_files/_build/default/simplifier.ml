open Ast

let collect_constant_strings code =
  let counter = ref 0 in
  let ccs_value ccs = function
    | V1.Nil    -> V2.Nil, ccs
    | V1.Bool b -> V2.Bool b, ccs
    | V1.Int n  -> V2.Int n, ccs
    | V1.Str s -> 
      (* let label = "str" ^ string_of_int !counter in 
      incr counter;
      V2.Data label, [(label, s)] *)
      if Env.mem s ccs then 
         V2.Data (Env.find s ccs), ccs
      else 
         incr counter;
         let label = "str" ^ string_of_int !counter in 
         V2.Data label, Env.add s l ccs
  in
  let rec ccs_expr = function
    | IR1.Value v ->
       let v, ccs = ccs_value v in
       IR2.Value v, ccs
    | IR1.Var v ->
       IR2.Var v, ccs
    | IR1.Call (f, args) ->
       (* let args2 = List.map ccs_expr args in
       let ccs = List.flatten (List.map (fun (_, s) -> s) args2) in
       IR2.Call (f, List.map (fun (e, _) -> e) args2), ccs *)
       let args2, ccs = List.fold_left 
                           (fun acc a -> 
                              let a2, ccs = ccs_expr (snd acc) a in
                              a2 :: (fst acc), ccs)
                           ([], ccs)
                           args in
       IR2.Call (f, args2), ccs
       
  in
  let ccs_lvalue ccs = function
    | IR1.LVar v  ->
       IR2.LVar v, ccs
    | IR1.LAddr a ->
       let a2, ccs = ccs_expr a in
       IR2.LAddr a2, ccs
  in
  let rec ccs_instr ccs = function
    | IR1.Decl v ->
       IR2.Decl v, ccs
    | IR1.Return e ->
       let e2, ccs = ccs_expr ccs e in
       IR2.Return e2, ccs
    | IR1.Expr e ->
       let e2, ccs = ccs_expr ccs e in
       IR2.Expr e2, ccs
    | IR1.Assign (lv, e) ->
       let lv2, ccs_lv = ccs_lvalue lv in
       let e2, ccs_e = ccs_expr e in
       IR2.Assign (lv2, e2), List.flatten [ ccs_lv ; ccs_e ]
    | IR1.Cond (t, y, n) ->
       let t2, ccs_t = ccs_expr t in
       let y2, ccs_y = ccs_block y in
       let n2, ccs_n = ccs_block n in
       IR2.Cond (t2, y2, n2), List.flatten [ ccs_t ; ccs_y ; ccs_n ]
  and ccs_block ccs = function
    | [] -> [], ccs
    | i :: r ->
       let i2, ccs_i = ccs_instr i in
       let r2, ccs_r = ccs_block r in
       i2 :: r2, List.flatten [ ccs_i ; ccs_r ]
  in
  let ccs_def ccs = function
    | IR1.Func (name, args, body) ->
       let body2, ccs = ccs_block body in
       IR2.Func (name, args, body2), ccs
  in
  let rec ccs_prog ccs = function
    | [] -> [], []
    | d :: r ->
       let d2, ccs_d = ccs_def ccs d in
       let r2, ccs_r = ccs_prog ccs r in
       d2 :: r2, ccs
  in 
  (* ccs_prog code *)
  let code2, ccs = ccs_prog Env.empty code in
  let strings, labels = List.spilt (Env.bindings ccs)
   in code2, List.combine labels strings

let simplify code =
  collect_constant_strings code

(* let output_data_section collected_strings =
   ".data\n" ^
   (collected_strings |> List.map (fun (label, s) -> label ^ " : .asciiz \"" ^ s ^ "\"\n") |> String.concat "") *)

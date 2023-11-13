open Print
open Ast
open Interp
open Baselib


let print_binding key value =
  (*print_string ("key : " ^ key ^ " value : "); print_value value; print_string " \n";;*)
  print_string (key ^ " = "); print_value value; print_string " \n";;
  (* usage : ```Env.iter print_binding env``` *)


    

let () =
  (*let to_do = [
    Assign ("test", Var_value(Int 333));
    Assign ("you", Var_value(Int 999));
    (*Return (Var_value(Int 101)) *)] in

  let ret = eval_block to_do Env.empty in
  match ret with
  | Ret valeur -> print_value valeur;
  | Env env -> print_string "renvoi d'env "; print_value (Env.find "you" env);;*)

  (*let v = Int 45 in
  let baselib = Env.add "test" (V v) baselib in
  let x = Env.find "test" baselib in
  match x with
  | V valeur -> print_value valeur
  | _ -> failwith "erreur";;*)

  (*let i = Assign ("test", (Var_value(Str "assez"))) in
  let ret = eva2_instr i baselib in
  print_string "\n";;*)

  let prog = [Assign("x", Var_value (Int 42))] in
  let _ = eval_block prog Env.empty in
  print_string "\n";;


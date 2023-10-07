

open Printf


(* Définition du type expr *)
type expr =
  | Num of int
  | Add of expr * expr
  | Sub of expr * expr
  | Mul of expr * expr
  | Div of expr * expr
  | Mod of expr * expr

(* Fonction d'affichage pour le type expr *)
let rec format e =
  match e with
  | Num n -> sprintf "%d" n
  | Add (e1, e2) -> format_binop "+" e1 e2
  | Sub (e1, e2) -> format_binop "-" e1 e2
  | Mul (e1, e2) -> format_binop "*" e1 e2
  | Div (e1, e2) -> format_binop "/" e1 e2
  | Mod (e1, e2) -> format_binop "%%" e1 e2

and format_binop op e1 e2 =
  let str_e1 = format e1 in
  let str_e2 = format e2 in
  match e1, e2 with
  | Add (_, _), _ | _, Add (_, _) -> sprintf "%s %s %s" str_e1 op str_e2 (* Pour afficher la format *)
  | _ -> sprintf "(%s %s %s)" str_e1 op str_e2

(* Fonction d'évaluation *)
let rec eval e =
  match e with
  | Num n -> n
  | Add (e1, e2) -> (eval e1) + (eval e2)
  | Sub (e1, e2) -> (eval e1) - (eval e2)
  | Mul (e1, e2) -> (eval e1) * (eval e2)
  | Div (e1, e2) -> (eval e1) / (eval e2)
  | Mod (e1, e2) -> (eval e1) mod (eval e2)



(** Tester **)

(* let e1 = Num 42 ;;
let e2 = Add (Num 10, Num 20) ;;
let e3 = Add (e1, e2) ;;
let result = eval e3 ;;
let formatted = format e3 ;; *)

(* let e1 = Num 3 ;;
let e2 = Add (Num 9, Num 8) ;;
let e3 = Mul (e1, Sub (Num 7, Num 2)) ;;
let result = eval e3 ;;
let formatted = format e3 ;; *)

let e1 = Num 1 ;;
let e2 = Add (Num 2, Num 3) ;;
let e3 = Add (Num 1, Mul (Num 2, Num 3)) ;;
let e4 = Mul (Num 1, Add (Num 2, Sub (Num 3, Num 4))) ;;
let result = eval e4 ;;
let formatted = format e4 ;;


(* Affichage du résultat *)
printf "Expression : %s\n" formatted ;;
printf "Résultat de l'évaluation : %d\n" result ;;


let () = 
  let  test = Mul (Num 3, Add (Num 4, Num 5)) in 
  printf "%s = %d\n" (format test) (eval test)




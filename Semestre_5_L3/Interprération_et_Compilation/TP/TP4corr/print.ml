open Ast

let rec print_value valeur =
  match valeur with
  | Void -> Printf.printf "nil"
  | Bool b -> Printf.printf "%B" b
  | Int i -> Printf.printf "%d" i
  | Str s -> Printf.printf "\"%s\"" s
  


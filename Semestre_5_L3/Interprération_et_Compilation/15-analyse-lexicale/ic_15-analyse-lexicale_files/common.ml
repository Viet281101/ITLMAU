type token =
  | Leof
  | Lfalse
  | Ltrue
  | Land
  | Lor
  | Lnot
  | Lopar
  | Lcpar
  | Lvar of string
  | Error

let string_of_token = function
  | Leof   -> "Leof"
  | Lfalse -> "Lfalse"
  | Ltrue  -> "Ltrue"
  | Land   -> "Land"
  | Lor    -> "Lor"
  | Lnot   -> "Lnot"
  | Lopar  -> "Lopar"
  | Lcpar  -> "Lcpar"
  | Lvar s -> "Lvar(" ^ s ^ ")"
  | Error  -> "Error"

let main get_token expr =
  let rec loop t =
    if t = Leof then ()
    else begin
        Printf.printf "%s\n" (string_of_token t) ;
        loop (get_token expr)
      end
  in loop (get_token expr)

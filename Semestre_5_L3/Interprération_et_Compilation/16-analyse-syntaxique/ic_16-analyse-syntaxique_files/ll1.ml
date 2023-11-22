(* ocamlbuild ll1.byte *)

open Lexer2

let current_token = ref Error

let get_token () =
  !current_token

let src = Lexing.from_string Sys.argv.(1)

let consume_token () =
  current_token := Lexer2.token src

let rec m_expr () =
  m_disj () ;
  m_disj_cont ()

and m_disj () =
  m_conj () ;
  m_conj_cont ()

and m_disj_cont () =
  match get_token () with
  | Lor ->
     m_Lor () ;
     m_expr ()
  | _ ->
     m_epsilon ()

and m_conj () =
  match get_token () with
  | Lopar ->
     m_Lopar () ;
     m_expr () ;
     m_Lcpar ()
  | Lnot ->
     m_conj ()
  | _ -> m_bit ()

and m_conj_cont () =
  match get_token () with
  | Land ->
     m_Land () ;
     m_expr ()
  | _ ->
     m_epsilon ()

and m_epsilon () = ()
and m_bit () =
  match get_token () with
  | Ltrue -> consume_token ()
  | Lfalse -> consume_token ()
  | _ -> failwith "Syntax error: expected bit"
and m_Land () =
  match get_token () with
  | Land -> consume_token ()
  | _ -> failwith "Syntax error: expected &&"
and m_Lor () =
  match get_token () with
  | Lor -> consume_token ()
  | _ -> failwith "Syntax error: expected ||"
and m_Lnot () =
  match get_token () with
  | Lnot -> consume_token ()
  | _ -> failwith "Syntax error: expected !"
and m_Lopar () =
  match get_token () with
  | Lopar -> consume_token ()
  | _ -> failwith "Syntax error: expected ("
and m_Lcpar () =
  match get_token () with
  | Lcpar -> consume_token ()
  | _ -> failwith "Syntax error: expected )"
and m_Leof () =
  match get_token () with
  | Leof -> ()
  | _ -> failwith "Syntax error: expected EOF"


let () =
  consume_token () ;
  m_expr () ;
  m_Leof () ;
  Printf.printf "syntax ok!\n"

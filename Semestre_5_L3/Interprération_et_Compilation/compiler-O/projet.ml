
open Lexing
open Ast
open Baselib

(* Base du projet sur le TP6
   Ainsi que, l'intégration des éléments des autres TP *)

let err msg pos =
  Printf.eprintf "Error on line %d col %d: %s.\n"
    pos.pos_lnum (pos.pos_cnum - pos.pos_bol) msg ;
  exit 1

let () =
  if (Array.length Sys.argv) != 2 then begin
      Printf.eprintf "Usage: %s <file>\n" Sys.argv.(0) ;
      exit 1
    end;
  let f = open_in Sys.argv.(1) in
  let buf = Lexing.from_channel f in
  try
    let parsed = Parser.start Lexer.token buf in
    close_in f ;
    Printf.eprintf "Parsed ok\n" ;
    let ast, env = Semantics.analyze parsed in
    Printf.eprintf "Semantic ok\n" ;
    let simplified = Simplifier.simplify ast in
    Printf.eprintf "Simplifier ok\n" ;
    let asm = Compiler.compile simplified env in
    Printf.eprintf "Compiler ok\n" ;
    let oc =  open_out "result.asm" in
    Mips.emit oc asm ;
    Printf.eprintf "Write ok\n" ;
  with
  | Lexer.Error c ->
     err (Printf.sprintf "unrecognized char '%c'" c) (Lexing.lexeme_start_p buf)
  | Parser.Error ->
     err "syntax error" (Lexing.lexeme_start_p buf)
  | Semantics.Error (msg, pos) ->
     err msg pos
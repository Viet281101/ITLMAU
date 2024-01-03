
(* The type of tokens. *)

type token = 
  | Lwhile
  | Ltypevoid
  | Ltypestr
  | Ltypeint
  | Ltypebool
  | Ltrue of (bool)
  | Lsuppeq
  | Lsupp
  | Lsub
  | Lstring of (string)
  | Lstar
  | Lsc
  | Lreturn
  | Lopar
  | Lobracket
  | Lneq
  | Lint of (int)
  | Linfeq
  | Linf
  | Lif
  | Lident of (string)
  | Lfalse of (bool)
  | Leq
  | Lend
  | Lelse
  | Ldiv
  | Ldeq
  | Lcpar
  | Lcomma
  | Lcbracket
  | Ladd

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.Syntax.block)

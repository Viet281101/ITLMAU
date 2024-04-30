
(* The type of tokens. *)

type token = 
  | Lvar of (string)
  | Lthen
  | Lsub
  | Lsc
  | Lreturn
  | Lopar
  | Lmul
  | Lint of (int)
  | Lif
  | Leq
  | Lend
  | Lelse
  | Ldiv
  | Lcpar
  | Lbool of (bool)
  | Lassign
  | Ladd

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val block: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.Syntax.block)

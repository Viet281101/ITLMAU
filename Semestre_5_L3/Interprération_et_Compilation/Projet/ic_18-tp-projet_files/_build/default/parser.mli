
(* The type of tokens. *)

type token = 
  | Lxor
  | Lwhile
  | Lvar of (string)
  | Ltype of (Ast.type_t)
  | Lsub
  | Lstring of (string)
  | Lsrl
  | Lsll
  | Lscanf
  | Lsc
  | Lreturn
  | Lprintf
  | Lprint_str
  | Lprint_nl
  | Lprint_int
  | Lprint_bool
  | Lor
  | Lopar
  | Locbra
  | Lnot
  | Lneq
  | Lmul
  | Lmod
  | Llte
  | Llt
  | Lint of (int)
  | Lif
  | Lgte
  | Lgt
  | Lexit
  | Leq
  | Lend
  | Lelse
  | Ldiv
  | Lcpar
  | Lcomma
  | Lccbra
  | Lbool of (bool)
  | Lassign
  | Land
  | Ladd

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val start: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.Syntax.prog)


(* The type of tokens. *)

type token = 
  | Lwhile
  | Lvar of (string)
  | Ltype of (Ast.type_t)
  | Lsub
  | Lstr of (string)
  | Lsne
  | Lslt
  | Lsle
  | Lsgt
  | Lsge
  | Lseq
  | Lsc
  | Lreturn
  | Lrem
  | Lparfin
  | Lpardeb
  | Lor
  | Lmul
  | Lint of (int)
  | Lif
  | Lend
  | Lelse
  | Ldiv
  | Lcomma
  | Lbracefin
  | Lbracedeb
  | Lbool of (bool)
  | Lassign
  | Land
  | Ladd

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.Syntax.prog)

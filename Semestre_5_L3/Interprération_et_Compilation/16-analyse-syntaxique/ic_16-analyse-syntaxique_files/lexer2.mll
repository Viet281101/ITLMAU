{
  type token =
  | Leof
  | Lfalse
  | Ltrue
  | Land
  | Lor
  | Lnot
  | Lopar
  | Lcpar
  | Error

  open Lexing
  exception Lexer of string
}

rule token = parse
| eof { Leof }
| [ ' ' '\t' '\n' ] { token lexbuf }
| "0"  { Lfalse }
| "1"  { Ltrue }
| "&&" { Land }
| "||" { Lor }
| "!"  { Lnot }
| "("  { Lopar }
| ")"  { Lcpar }
| _ as c { raise (Lexer (Printf.sprintf "Unrecognized char '%c' at offset %d."
                                           c lexbuf.lex_curr_p.pos_cnum)) }

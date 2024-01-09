{
  (* ocamlbuild lexer.byte *)

  open Common

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
| ['a'-'z' 'A'-'Z']+ as l { Lvar (l) }
| _ as c { raise (Lexer (Printf.sprintf "Unrecognized char '%c' at offset %d."
                                           c lexbuf.lex_curr_p.pos_cnum)) }

{
  main token (Lexing.from_string Sys.argv.(1))
}

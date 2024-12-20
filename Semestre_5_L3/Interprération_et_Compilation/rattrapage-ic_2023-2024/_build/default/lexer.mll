{
	open Parser

	exception Error of char
}

let alpha = ['a'-'z' 'A'-'Z']
let num = ['0'-'9']
let identifier = alpha (alpha | num | '-' | '_')*

rule token = parse
| eof             { Lend }
| [ ' ' '\t' ]    { token lexbuf }
| '\n'            { Lexing.new_line lexbuf; token lexbuf }
| '#'             { comment lexbuf }
| "true"          { Lbool true }
| "false"         { Lbool false }
| "+"             { Ladd }
| "-"             { Lsub }
| "*"             { Lmul }
| "/"             { Ldiv }
| "("             { Lopar }
| ")"             { Lcpar }
| "return"        { Lreturn }
| "="             { Lassign }
| ";"             { Lsc }
| "=="            { Leq }
| "if"            { Lif }
| "then"          { Lthen }
| "else"          { Lelse }
| identifier as s { Lvar (s) }
| num+ as n       { Lint (int_of_string n) }
| _ as c          { raise (Error c) }

and comment = parse
| eof  { Lend }
| '\n' { Lexing.new_line lexbuf; token lexbuf }
| _    { comment lexbuf }

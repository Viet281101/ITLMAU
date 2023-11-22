%{
  open Ast
%}

%token Lfalse Ltrue
%token Land Lor Lnot
%token Lopar Lcpar
%token Leof

%left Lor
%left Land
%right Lnot

%start prog

%type <Ast.expr> prog

%%

prog:
| e = expr; Leof { e }
;

expr:
| a = expr; Land; b = expr { And (a, b) }
| a = expr; Lor; b = expr  { Or  (a, b) }
| Lnot; e = expr           { Not (e) }
| Lopar; e = expr; Lcpar   { e }
| Lfalse                   { Bit (false) }
| Ltrue                    { Bit (true) }
;

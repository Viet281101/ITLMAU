%{
	open Ast.Syntax
%}

%token <int> Lint
%token <string> Lvar
%token Ladd Lsub Lmul Ldiv Lopar Lcpar
%token Lreturn Lassign Lsc Lend

%left Ladd Lsub
%left Lmul Ldiv

%start block

%type <Ast.Syntax.block> block

%%

block:
| v = Lvar; Lassign; e = expr; Lsc; b = block {
	Assign { var = v ; expr = e ; pos = $startpos($2) }
	:: b
}
| Lreturn; e = expr; Lsc; b = block {
	Return { expr = e ; pos = $startpos($3) }
	:: b
}
| Lend { [] }
;

expr:
| n = Lint {
	Val { value = Int (n) ; pos = $startpos }
}
| Lsub; n = Lint {
	Val { value = Int (-n) ; pos = $startpos }
}
| n = Lvar {
	Var { name = n ; pos = $startpos }
}
| a = expr; Ladd; b = expr {
	Cal { func = "%add" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lsub; b = expr {
	Cal { func = "%sub" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lmul; b = expr {
	Cal { func = "%mul" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Ldiv; b = expr {
	Cal { func = "%div" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| Lopar; e = expr; Lcpar { e }
;

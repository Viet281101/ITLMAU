%{
	open Ast.Syntax
%}

%token <int> Lint
%token <string> Lvar
%token <bool> Lbool
%token Ladd Lsub Lmul Ldiv Lopar Lcpar Leq
%token Lreturn Lassign Lsc Lend Lif Lthen Lelse

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
| b = Lbool {
	Val { value = Bool (b) ; pos = $startpos }
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
| a = expr; Leq; b = expr {
	Cal { func = "%eq"; args = [ a; b ]; pos = $startpos($2) }
}
| Lopar; e = expr; Lcpar { e }
| Lopar; Lif; cond = expr; Lthen; e1 = expr; Lelse; e2 = expr; Lcpar {
	If { condition = cond; then_branch = e1; else_branch = e2; pos = $startpos }
}
;

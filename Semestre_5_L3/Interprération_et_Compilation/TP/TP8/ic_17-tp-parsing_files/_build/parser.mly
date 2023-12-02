%{
  open Ast
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
  | Lend { [] }
  | i = instr ; b = block { i :: b }
;

instr:
  | Lreturn; e = expr; Lsc { 
    Return { expr = e; pos = $startpos($1) } 
  }
;

expr:
  | n = Lint {
    Int { value = n; pos = $startpos }
  }
  
;

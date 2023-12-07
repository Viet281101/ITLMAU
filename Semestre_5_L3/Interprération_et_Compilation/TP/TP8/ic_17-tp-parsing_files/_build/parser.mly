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
  | v = Lvar; Lassign; e = expr; Lsc {
      Assign {
        var = v;
        expr = e;
        pos = $startpos(v)
      }
    }
  | Lreturn; e = expr; Lsc { 
    Return { expr = e; pos = $startpos($1) } 
  }
;

expr:
  | n = Lint {
      Int { value = n; pos = $startpos }
    }
  | v = Lvar {
      Var { name = v; pos = $startpos(v) }
    }
  | e1 = expr; Lmul; e2 = expr {
      Call {
        func = "%mul";
        args = [e1; e2];
        pos = $startpos(e1)
      }
    }
  | e1 = expr; Ldiv; e2 = expr {
      Call {
        func = "%div";
        args = [e1; e2];
        pos = $startpos(e1)
      }
    }
  | e1 = expr; Ladd; e2 = expr {
      Call {
        func = "%add";
        args = [e1; e2];
        pos = $startpos(e1)
      }
    }
  | e1 = expr; Lsub; e2 = expr {
      Call {
        func = "%sub";
        args = [e1; e2];
        pos = $startpos(e1)
      }
    }
;

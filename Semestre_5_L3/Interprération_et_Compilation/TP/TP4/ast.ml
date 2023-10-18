
module IR = struct
  type ident = string

  type value = 
  | Nil
  | Bool pf bool
  | Int of int
  | Str of string

  type expr =
  | value of value
  | Var of ident
  | Call of ident * expr list

  type instr = 
  | Return of expr
  | Expr of expr 
  | Assign of ident * expr
  | Cond of expr * block * block
  | Loop of expr * block
  and block = instr list

  type def = 
  | Func of ident * ident list * block

  type prog = def list
end

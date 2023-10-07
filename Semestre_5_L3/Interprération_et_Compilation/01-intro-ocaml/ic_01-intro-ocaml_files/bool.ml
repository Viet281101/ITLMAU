open Ast.Bool
open Ast.Nand

(* formulas taken from https://en.wikipedia.org/wiki/NAND_logic *)
let rec compile = function
  | Bool b     -> B b
  | Not e      -> let ce = compile e in N (ce, ce)
  | And (a, b) -> let ca, cb = compile a, compile b in
                  N (N (ca, cb), N (ca, cb))
  | Or (a, b)  -> let ca, cb = compile a, compile b in
                  N (N (ca, ca), N (cb, cb))
  | Xor (a, b) -> let ca, cb = compile a, compile b in
                  N (N (ca, N (ca, cb)), N (cb, N (ca, cb)))

(* bonus: eval, useless in our compiler except to make some tests *)
let rec eval = function
  | Bool b     -> b
  | Not e      -> not (eval e)
  | And (a, b) -> (eval a) && (eval b)
  | Or (a, b)  -> (eval a) || (eval b)
  | Xor (a, b) -> (eval a) <> (eval b)

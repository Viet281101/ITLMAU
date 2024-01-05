open Ast
open Mips

module Env = Map.Make(String)
module Pile = Stack
let _types_ = 
    List.fold_left
        (fun env (pris, typ) -> Env.add pris typ env)
        Env.empty
        [ "_add",  Func_t (Int_t , [ Int_t ; Int_t ])
         ;"_sub",  Func_t (Int_t , [ Int_t ; Int_t ])
         ;"_mul",  Func_t (Int_t , [ Int_t ; Int_t ])
         ;"_div",  Func_t (Int_t , [ Int_t ; Int_t ])
         ;"_mod",  Func_t (Int_t , [ Int_t ; Int_t ])
         
         ;"puti",  Func_t (Nil_t , [ Int_t])
         ;"puts",  Func_t (Nil_t , [ Str_t])
         ;"putb",  Func_t (Nil_t , [ Bool_t])
         ;"putnl", Func_t (Nil_t , [ ])
         ;"geti",  Func_t (Int_t , [ ])
         ;"exit",  Func_t (Nil_t , [ ])

         ;"_eq" ,  Func_t (Bool_t, [ Int_t ; Int_t ])
         ;"_neq",  Func_t (Bool_t, [ Int_t ; Int_t ])

         ;"_sll" ,  Func_t (Int_t, [ Int_t ; Int_t ])
         ;"_srl",   Func_t (Int_t, [ Int_t ; Int_t ])

         ;"_gt" ,  Func_t (Bool_t, [ Int_t ; Int_t ])
         ;"_gte",  Func_t (Bool_t, [ Int_t ; Int_t ])
         ;"_lt" ,  Func_t (Bool_t, [ Int_t ; Int_t ])
         ;"_lte",  Func_t (Bool_t, [ Int_t ; Int_t ])

         ;"_or" ,  Func_t (Bool_t, [ Bool_t ; Bool_t ])
         ;"_and",  Func_t (Bool_t, [ Bool_t ; Bool_t ])
         ;"_xor",  Func_t (Int_t , [ Int_t ; Int_t ])

         ;"_not",  Func_t (Bool_t, [ Int_t])
        ]

let builtins =
  [ 
    Label "_add"
    ; Lw (T0, Mem (SP, 0))
    ; Lw (T1, Mem (SP, 4))
    ; Add (V0, T0, T1)
    ; Jr RA

    ;Label "_sub"
    ; Lw (T0, Mem (SP, 0))
    ; Lw (T1, Mem (SP, 4))
    ; Sub (V0, T1, T0)
    ; Jr RA

    ; Label "_mul"
    ; Lw (T0, Mem (SP, 0))
    ; Lw (T1, Mem (SP, 4))
    ; Mul (V0, T0, T1)
    ; Jr RA

    ; Label "_div"
    ; Lw (T0, Mem (SP, 0))
    ; Lw (T1, Mem (SP, 4))
    ; Div (V0, T1, T0)
    ; Jr RA

    ; Label "_mod"
    ; Lw (T0, Mem (SP, 0))
    ; Lw (T1, Mem (SP, 4))
    ; Div (V0, T1, T0)
    ; Mfhi V0
    ; Jr RA

    ; Label "puti"
    ; Lw (A0, Mem (SP, 0))
    ; Li (V0, Syscall.print_int)
    ; Syscall
    ; Jr RA

    ; Label "putnl"
    ; La (A0, (Lbl "nl"))
    ; Li (V0, Syscall.print_str)
    ; Syscall
    ; Jr RA

    ; Label "exit"
    ; Li (V0, 0)
    ; Syscall

    ; Label "geti"
    ; Lw (A0, Mem (SP, 0))
    ; Li (V0, Syscall.read_int)
    ; Syscall
    ; Jr RA

    ; Label "puts"
    ; Move (A0, V0)
    ; Li (V0, Syscall.print_str)
    ; Syscall
    ; Jr RA

    ; Label "putb"
    ; Move (A0, V0)
    ; Li (V0, Syscall.print_int)
    ; Syscall
    ; Jr RA
    (*  *)
    ; Label "_gt"
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Sgt (V0, T0, T1)
    ; Jr RA

    ; Label "_sll"
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Sll (V0, T0, T1)
    ; Jr RA

    ; Label "_srl"
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Srl (V0, T0, T1)
    ; Jr RA

    ; Label "_gte" 
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Sge (V0, T0, T1)
    ; Jr RA

    ; Label "_lt" 
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Slt (V0, T0, T1)
    ; Jr RA

    ; Label "_lte" 
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Sle (V0 ,T0,T1)
    ; Jr RA

    ; Label "_eq" 
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Seq (V0,T0,T1) 
    ; Jr RA

    ; Label "_neq"
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Sne (V0, T0, T1)
    ; Jr RA

    ; Label "_and" 
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; And (V0, T0, T1)
    ; Jr RA

    ; Label "_or"  
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Or (V0, T0, T1)
    ; Jr RA

    ; Label "_xor" 
    ; Lw (T0, Mem (SP, 4))
    ; Lw (T1, Mem (SP, 0))
    ; Xor(V0, T0, T1)
    ; Jr RA

    ; Label "_not"
    ; Not (V0, V0)
    ; Jr RA
  ]
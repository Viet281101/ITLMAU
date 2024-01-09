(* ocamlbuild -pkgs str hand.byte *)

open Common

let alpha = Str.regexp "[a-z]"

let token src =
  let rec loop n =
    match n with
    | None -> Leof
    | Some c ->
       Stream.junk src ;
       match c with
       | ' ' | '\n' | '\t' -> loop (Stream.peek src)
       | '0' -> Lfalse
       | '1' -> Ltrue
       | '&' ->
          (match Stream.peek src with
           | Some '&' -> Stream.junk src ; Land
           | _ -> Error)
       | '|' ->
          (match Stream.peek src with
           | Some '|' -> Stream.junk src ; Lor
           | _ -> Error)
       | '!' -> Lnot
       | '(' -> Lopar
       | ')' -> Lcpar
       | c when Str.string_match alpha (String.make 1 c) 0 ->
          let rec var_loop n buf =
            match n with
            | Some (c) when Str.string_match alpha (String.make 1 c) 0 ->
               Stream.junk src ;
               var_loop (Stream.peek src) (buf ^ (String.make 1 c))
            | _ -> Lvar buf
          in var_loop (Stream.peek src) (String.make 1 c)
       | _ -> Error
  in loop (Stream.peek src)

let () =
  main token (Stream.of_string Sys.argv.(1))

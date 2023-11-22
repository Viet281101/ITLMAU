(* ocamlbuild auto.byte *)

open Common

let return state buf =
  match state with
  | 1 -> Lfalse
  | 2 -> Ltrue
  | 4 -> Land
  | 6 -> Lor
  | 7 -> Lnot
  | 8 -> Lopar
  | 9 -> Lcpar
  | 10 -> Lvar (buf) (* hack for when EOF encountered while reading var name *)
  | 11 -> Lvar (buf)
  | 12 -> Error
  | _ -> Leof

let nb_states = 12
let transitions = Array.make_matrix nb_states 256 nb_states
let final = [ 1 ; 2 ; 4 ; 6 ; 7 ; 8 ; 9 ; 11 ; 12 ]
let has_buf = [ 11 ]

let () =
  transitions.(0).(Char.code ' ') <- 0 ;
  transitions.(0).(Char.code '\n') <- 0 ;
  transitions.(0).(Char.code '\t') <- 0 ;

  transitions.(0).(Char.code '0') <- 1 ;

  transitions.(0).(Char.code '1') <- 2 ;

  transitions.(0).(Char.code '&') <- 3 ;
  transitions.(3).(Char.code '&') <- 4 ;

  transitions.(0).(Char.code '|') <- 5 ;
  transitions.(5).(Char.code '|') <- 6 ;

  transitions.(0).(Char.code '!') <- 7 ;

  transitions.(0).(Char.code '(') <- 8 ;

  transitions.(0).(Char.code ')') <- 9 ;

  for c = 0 to 255 do transitions.(10).(c) <- 11 done ;
  for c = Char.code 'a' to Char.code 'z' do
    transitions.(0).(c) <- 10 ;
    transitions.(10).(c) <- 10
  done ;

  let token src =
    let rec automaton state buf =
      match Stream.peek src with
      | None -> return state buf
      | Some c ->
         let next_state = transitions.(state).(Char.code c) in
         if List.mem next_state final then begin
             if List.mem next_state has_buf then () else Stream.junk src ;
             return next_state buf
           end
         else
           automaton next_state
             (let c = String.make 1 (Stream.next src) in
              if next_state = state then (buf ^ c) else c)
    in automaton 0 ""
  in
  main token (Stream.of_string Sys.argv.(1))

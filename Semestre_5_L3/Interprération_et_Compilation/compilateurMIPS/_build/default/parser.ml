
module MenhirBasics = struct
  
  exception Error
  
  let _eRR : exn =
    Error
  
  type token = 
    | Lwhile
    | Lvar of (
# 10 "parser.mly"
       (string)
# 15 "parser.ml"
  )
    | Ltype of (
# 9 "parser.mly"
       (Ast.type_t)
# 20 "parser.ml"
  )
    | Lsub
    | Lstr of (
# 8 "parser.mly"
       (string)
# 26 "parser.ml"
  )
    | Lsne
    | Lslt
    | Lsle
    | Lsgt
    | Lsge
    | Lseq
    | Lsc
    | Lreturn
    | Lrem
    | Lparfin
    | Lpardeb
    | Lor
    | Lmul
    | Lint of (
# 6 "parser.mly"
       (int)
# 44 "parser.ml"
  )
    | Lif
    | Lend
    | Lelse
    | Ldiv
    | Lcomma
    | Lbracefin
    | Lbracedeb
    | Lbool of (
# 7 "parser.mly"
       (bool)
# 56 "parser.ml"
  )
    | Lassign
    | Land
    | Ladd
  
end

include MenhirBasics

type _menhir_env = {
  _menhir_lexer: Lexing.lexbuf -> token;
  _menhir_lexbuf: Lexing.lexbuf;
  _menhir_token: token;
  mutable _menhir_error: bool
}

and _menhir_state = 
  | MenhirState87
  | MenhirState83
  | MenhirState78
  | MenhirState72
  | MenhirState71
  | MenhirState69
  | MenhirState67
  | MenhirState62
  | MenhirState59
  | MenhirState53
  | MenhirState51
  | MenhirState48
  | MenhirState46
  | MenhirState44
  | MenhirState42
  | MenhirState40
  | MenhirState38
  | MenhirState36
  | MenhirState34
  | MenhirState32
  | MenhirState30
  | MenhirState28
  | MenhirState26
  | MenhirState24
  | MenhirState22
  | MenhirState12
  | MenhirState10
  | MenhirState8
  | MenhirState3
  | MenhirState0

# 1 "parser.mly"
  
  open Ast
  open Ast.Syntax

# 110 "parser.ml"

let rec _menhir_goto_loption_separated_nonempty_list_Lcomma_expr__ : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.expr list) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    let _menhir_stack = Obj.magic _menhir_stack in
    assert (not _menhir_env._menhir_error);
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lparfin ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_env = _menhir_discard _menhir_env in
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, (f : (
# 10 "parser.mly"
       (string)
# 126 "parser.ml"
        )), _startpos_f_), _, (xs : (Ast.Syntax.expr list))) = _menhir_stack in
        let _startpos = _startpos_f_ in
        let _v : (Ast.Syntax.expr) = let a = 
# 232 "<standard.mly>"
    ( xs )
# 132 "parser.ml"
         in
        let _startpos = _startpos_f_ in
        
# 198 "parser.mly"
                                                                    (
    Call { func = f ; args = a ; pos = _startpos }
  )
# 140 "parser.ml"
         in
        _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_goto_separated_nonempty_list_Lcomma_expr_ : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.expr list) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    match _menhir_s with
    | MenhirState12 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (x : (Ast.Syntax.expr list)) = _v in
        let _v : (Ast.Syntax.expr list) = 
# 144 "<standard.mly>"
    ( x )
# 160 "parser.ml"
         in
        _menhir_goto_loption_separated_nonempty_list_Lcomma_expr__ _menhir_env _menhir_stack _menhir_s _v
    | MenhirState46 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (xs : (Ast.Syntax.expr list)) = _v in
        let (_menhir_stack, _menhir_s, (x : (Ast.Syntax.expr)), _startpos_x_) = _menhir_stack in
        let _v : (Ast.Syntax.expr list) = 
# 243 "<standard.mly>"
    ( x :: xs )
# 171 "parser.ml"
         in
        _menhir_goto_separated_nonempty_list_Lcomma_expr_ _menhir_env _menhir_stack _menhir_s _v
    | _ ->
        _menhir_fail ()

and _menhir_run22 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState22 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState22 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState22 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState22 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState22 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState22

and _menhir_run34 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState34 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState34 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState34 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState34 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState34 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState34

and _menhir_run36 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState36 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState36 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState36 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState36 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState36 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState36

and _menhir_run38 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState38 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState38 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState38 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState38 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState38 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState38

and _menhir_run40 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState40 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState40 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState40 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState40 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState40 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState40

and _menhir_run42 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState42 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState42 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState42 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState42 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState42 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState42

and _menhir_run44 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState44 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState44 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState44 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState44 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState44 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState44

and _menhir_run24 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState24 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState24 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState24 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState24 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState24 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState24

and _menhir_run26 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState26 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState26 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState26 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState26 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState26 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState26

and _menhir_run30 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState30 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState30 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState30 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState30 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState30 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState30

and _menhir_run32 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState32 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState32 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState32 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState32 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState32 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState32

and _menhir_run28 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState28 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState28 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState28 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState28 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState28 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState28

and _menhir_run48 : _menhir_env -> 'ttv_tail * _menhir_state * (Ast.Syntax.expr) * Lexing.position -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _startpos ->
    let _menhir_stack = (_menhir_stack, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState48 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState48 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState48 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState48 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState48 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState48

and _menhir_reduce10 : _menhir_env -> 'ttv_tail * _menhir_state * (
# 10 "parser.mly"
       (string)
# 453 "parser.ml"
) * Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack ->
    let (_menhir_stack, _menhir_s, (v : (
# 10 "parser.mly"
       (string)
# 459 "parser.ml"
    )), _startpos_v_) = _menhir_stack in
    let _startpos = _startpos_v_ in
    let _v : (Ast.Syntax.expr) = let _startpos = _startpos_v_ in
    
# 128 "parser.mly"
             (
    Var { name = v ; pos = _startpos }
  )
# 468 "parser.ml"
     in
    _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos

and _menhir_run12 : _menhir_env -> 'ttv_tail * _menhir_state * (
# 10 "parser.mly"
       (string)
# 475 "parser.ml"
) * Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState12 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState12 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState12 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState12 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState12 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lparfin ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_s = MenhirState12 in
        let _v : (Ast.Syntax.expr list) = 
# 142 "<standard.mly>"
    ( [] )
# 497 "parser.ml"
         in
        _menhir_goto_loption_separated_nonempty_list_Lcomma_expr__ _menhir_env _menhir_stack _menhir_s _v
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState12

and _menhir_goto_instr : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.instr list) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    let _menhir_stack = Obj.magic _menhir_stack in
    assert (not _menhir_env._menhir_error);
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lbracedeb ->
        _menhir_run71 _menhir_env (Obj.magic _menhir_stack) MenhirState72
    | Lbracefin ->
        _menhir_run70 _menhir_env (Obj.magic _menhir_stack) MenhirState72
    | Lif ->
        _menhir_run66 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lreturn ->
        _menhir_run62 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Ltype _v ->
        _menhir_run56 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run52 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lwhile ->
        _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState72 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState72

and _menhir_run11 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 10 "parser.mly"
       (string)
# 542 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lpardeb ->
        _menhir_run12 _menhir_env (Obj.magic _menhir_stack)
    | Ladd | Land | Lcomma | Ldiv | Lmul | Lor | Lparfin | Lrem | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
        _menhir_reduce10 _menhir_env (Obj.magic _menhir_stack)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_goto_block : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.block) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    match _menhir_s with
    | MenhirState72 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, (i : (Ast.Syntax.instr list))), _, (b : (Ast.Syntax.block))) = _menhir_stack in
        let _v : (Ast.Syntax.block) = 
# 54 "parser.mly"
                          ( i @ b )
# 571 "parser.ml"
         in
        _menhir_goto_block _menhir_env _menhir_stack _menhir_s _v
    | MenhirState71 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s), _, (b : (Ast.Syntax.block))) = _menhir_stack in
        let _v : (Ast.Syntax.block) = 
# 51 "parser.mly"
                          ( b )
# 581 "parser.ml"
         in
        _menhir_goto_block _menhir_env _menhir_stack _menhir_s _v
    | MenhirState69 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lelse ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | Lbool _v ->
                _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lbracedeb ->
                _menhir_run71 _menhir_env (Obj.magic _menhir_stack) MenhirState78
            | Lbracefin ->
                _menhir_run70 _menhir_env (Obj.magic _menhir_stack) MenhirState78
            | Lif ->
                _menhir_run66 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lint _v ->
                _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lreturn ->
                _menhir_run62 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lstr _v ->
                _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lsub ->
                _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Ltype _v ->
                _menhir_run56 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lvar _v ->
                _menhir_run52 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lwhile ->
                _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState78 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState78)
        | Lbool _ | Lbracedeb | Lbracefin | Lif | Lint _ | Lreturn | Lstr _ | Lsub | Ltype _ | Lvar _ | Lwhile ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, _startpos__1_), _, (e : (Ast.Syntax.expr)), _startpos_e_), _, (b : (Ast.Syntax.block))) = _menhir_stack in
            let _v : (Ast.Syntax.instr list) = let _startpos = _startpos__1_ in
            
# 97 "parser.mly"
                                                   (
    [ Cond { expr = e ; if_b = b ; else_b = [] ; pos = _startpos } ]
  )
# 629 "parser.ml"
             in
            _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState78 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((((_menhir_stack, _menhir_s, _startpos__1_), _, (e : (Ast.Syntax.expr)), _startpos_e_), _, (b1 : (Ast.Syntax.block))), _, (b2 : (Ast.Syntax.block))) = _menhir_stack in
        let _v : (Ast.Syntax.instr list) = let _startpos = _startpos__1_ in
        
# 92 "parser.mly"
                                                                         (
    [ Cond { expr = e ; if_b = b1 ; else_b = b2 ; pos = _startpos } ]
  )
# 648 "parser.ml"
         in
        _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
    | MenhirState51 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (((_menhir_stack, _menhir_s, _startpos__1_), _, (e : (Ast.Syntax.expr)), _startpos_e_), _, (b : (Ast.Syntax.block))) = _menhir_stack in
        let _v : (Ast.Syntax.instr list) = let _startpos = _startpos__1_ in
        
# 102 "parser.mly"
                                                      (
    [ Loop { expr = e ; block = b ; pos = _startpos } ]
  )
# 661 "parser.ml"
         in
        _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
    | MenhirState8 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((((_menhir_stack, _menhir_s, (t : (
# 9 "parser.mly"
       (Ast.type_t)
# 670 "parser.ml"
        )), _startpos_t_), (f : (
# 10 "parser.mly"
       (string)
# 674 "parser.ml"
        )), _startpos_f_), _, (xs : (Ast.Syntax.args))), _, (b : (Ast.Syntax.block))) = _menhir_stack in
        let _v : (Ast.Syntax.def list) = let a = 
# 232 "<standard.mly>"
    ( xs )
# 679 "parser.ml"
         in
        
# 41 "parser.mly"
              (
    [ Func { func = f ; type_t = t ; args = a ; code = b ; pos = _startpos_f_ } ]
  )
# 686 "parser.ml"
         in
        let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lend ->
            _menhir_run85 _menhir_env (Obj.magic _menhir_stack) MenhirState87
        | Ltype _v ->
            _menhir_run1 _menhir_env (Obj.magic _menhir_stack) MenhirState87 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState87)
    | _ ->
        _menhir_fail ()

and _menhir_goto_expr : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.expr) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v, _startpos) in
    match _menhir_s with
    | MenhirState46 | MenhirState12 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Ladd ->
            _menhir_run48 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lcomma ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | Lbool _v ->
                _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState46 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lint _v ->
                _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState46 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lstr _v ->
                _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState46 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lsub ->
                _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState46 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lvar _v ->
                _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState46 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState46)
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lseq ->
            _menhir_run44 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsge ->
            _menhir_run42 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsgt ->
            _menhir_run40 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsle ->
            _menhir_run38 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lslt ->
            _menhir_run36 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsne ->
            _menhir_run34 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run22 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lparfin ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, (x : (Ast.Syntax.expr)), _startpos_x_) = _menhir_stack in
            let _v : (Ast.Syntax.expr list) = 
# 241 "<standard.mly>"
    ( [ x ] )
# 764 "parser.ml"
             in
            _menhir_goto_separated_nonempty_list_Lcomma_expr_ _menhir_env _menhir_stack _menhir_s _v
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState22 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 138 "parser.mly"
                               (
    Call { func = "%sub" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 797 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState24 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Ldiv | Lmul | Lparfin | Lrem | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 153 "parser.mly"
                               (
    Call { func = "%rem" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 824 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState26 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
        let _startpos = _startpos_a_ in
        let _v : (Ast.Syntax.expr) = 
# 193 "parser.mly"
                              (
    Call { func = "%or" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 843 "parser.ml"
         in
        _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
    | MenhirState28 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
        let _startpos = _startpos_a_ in
        let _v : (Ast.Syntax.expr) = 
# 188 "parser.mly"
                               (
    Call { func = "%and" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 856 "parser.ml"
         in
        _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
    | MenhirState30 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Ldiv | Lmul | Lparfin | Lrem | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 143 "parser.mly"
                               (
    Call { func = "%mul" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 877 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState32 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Ldiv | Lmul | Lparfin | Lrem | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 148 "parser.mly"
                               (
    Call { func = "%div" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 904 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState34 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 183 "parser.mly"
                               (
    Call { func = "%sne" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 937 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState36 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 178 "parser.mly"
                               (
    Call { func = "%slt" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 970 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState38 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 173 "parser.mly"
                               (
    Call { func = "%sle" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 1003 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState40 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 168 "parser.mly"
                               (
    Call { func = "%sgt" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 1036 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState42 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 163 "parser.mly"
                               (
    Call { func = "%sge" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 1069 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState44 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 158 "parser.mly"
                               (
    Call { func = "%seq" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 1102 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState48 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ladd | Lcomma | Lparfin | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s, (a : (Ast.Syntax.expr)), _startpos_a_), _startpos__2_), _, (b : (Ast.Syntax.expr)), _startpos_b_) = _menhir_stack in
            let _startpos = _startpos_a_ in
            let _v : (Ast.Syntax.expr) = 
# 133 "parser.mly"
                               (
    Call { func = "%add" ; args = [ a ; b ] ; pos = _startpos__2_ }
  )
# 1135 "parser.ml"
             in
            _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState10 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Ladd ->
            _menhir_run48 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lparfin ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | Lbool _v ->
                _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lbracedeb ->
                _menhir_run71 _menhir_env (Obj.magic _menhir_stack) MenhirState51
            | Lbracefin ->
                _menhir_run70 _menhir_env (Obj.magic _menhir_stack) MenhirState51
            | Lif ->
                _menhir_run66 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lint _v ->
                _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lreturn ->
                _menhir_run62 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lstr _v ->
                _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lsub ->
                _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Ltype _v ->
                _menhir_run56 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lvar _v ->
                _menhir_run52 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lwhile ->
                _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState51 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState51)
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lseq ->
            _menhir_run44 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsge ->
            _menhir_run42 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsgt ->
            _menhir_run40 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsle ->
            _menhir_run38 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lslt ->
            _menhir_run36 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsne ->
            _menhir_run34 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run22 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState53 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Ladd ->
            _menhir_run48 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsc ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
            let _menhir_env = _menhir_discard _menhir_env in
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos__4_ = _startpos in
            let (((_menhir_stack, _menhir_s, (v : (
# 10 "parser.mly"
       (string)
# 1238 "parser.ml"
            )), _startpos_v_), _startpos__2_), _, (e : (Ast.Syntax.expr)), _startpos_e_) = _menhir_stack in
            let _v : (Ast.Syntax.instr list) = 
# 82 "parser.mly"
                                        (
    [ Assign { var = v ; expr = e ; pos = _startpos__2_ } ]
  )
# 1245 "parser.ml"
             in
            _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
        | Lseq ->
            _menhir_run44 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsge ->
            _menhir_run42 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsgt ->
            _menhir_run40 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsle ->
            _menhir_run38 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lslt ->
            _menhir_run36 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsne ->
            _menhir_run34 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run22 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState59 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Ladd ->
            _menhir_run48 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsc ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
            let _menhir_env = _menhir_discard _menhir_env in
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos__5_ = _startpos in
            let ((((_menhir_stack, _menhir_s, (t : (
# 9 "parser.mly"
       (Ast.type_t)
# 1294 "parser.ml"
            )), _startpos_t_), (v : (
# 10 "parser.mly"
       (string)
# 1298 "parser.ml"
            )), _startpos_v_), _startpos__3_), _, (e : (Ast.Syntax.expr)), _startpos_e_) = _menhir_stack in
            let _v : (Ast.Syntax.instr list) = 
# 77 "parser.mly"
    ( [ Decl { name = v ; type_t = t ; pos = _startpos_v_ }
    ; Assign { var = v ; expr = e ; pos = _startpos__3_ } ]
    )
# 1305 "parser.ml"
             in
            _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
        | Lseq ->
            _menhir_run44 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsge ->
            _menhir_run42 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsgt ->
            _menhir_run40 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsle ->
            _menhir_run38 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lslt ->
            _menhir_run36 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsne ->
            _menhir_run34 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run22 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState62 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Ladd ->
            _menhir_run48 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsc ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
            let _menhir_env = _menhir_discard _menhir_env in
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos__3_ = _startpos in
            let ((_menhir_stack, _menhir_s, _startpos__1_), _, (e : (Ast.Syntax.expr)), _startpos_e_) = _menhir_stack in
            let _v : (Ast.Syntax.instr list) = let _startpos = _startpos__1_ in
            
# 62 "parser.mly"
                             ( [ Return { expr = e ; pos = _startpos } ] )
# 1356 "parser.ml"
             in
            _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
        | Lseq ->
            _menhir_run44 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsge ->
            _menhir_run42 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsgt ->
            _menhir_run40 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsle ->
            _menhir_run38 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lslt ->
            _menhir_run36 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsne ->
            _menhir_run34 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run22 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState67 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Ladd ->
            _menhir_run48 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lparfin ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | Lbool _v ->
                _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lbracedeb ->
                _menhir_run71 _menhir_env (Obj.magic _menhir_stack) MenhirState69
            | Lbracefin ->
                _menhir_run70 _menhir_env (Obj.magic _menhir_stack) MenhirState69
            | Lif ->
                _menhir_run66 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lint _v ->
                _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lreturn ->
                _menhir_run62 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lstr _v ->
                _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lsub ->
                _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Ltype _v ->
                _menhir_run56 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lvar _v ->
                _menhir_run52 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lwhile ->
                _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState69 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState69)
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lseq ->
            _menhir_run44 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsge ->
            _menhir_run42 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsgt ->
            _menhir_run40 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsle ->
            _menhir_run38 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lslt ->
            _menhir_run36 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsne ->
            _menhir_run34 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run22 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState8 | MenhirState51 | MenhirState78 | MenhirState69 | MenhirState71 | MenhirState72 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Ladd ->
            _menhir_run48 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Land ->
            _menhir_run28 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ldiv ->
            _menhir_run32 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lmul ->
            _menhir_run30 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lor ->
            _menhir_run26 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lrem ->
            _menhir_run24 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsc ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
            let _menhir_env = _menhir_discard _menhir_env in
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos__2_ = _startpos in
            let (_menhir_stack, _menhir_s, (e : (Ast.Syntax.expr)), _startpos_e_) = _menhir_stack in
            let _v : (Ast.Syntax.instr list) = let _startpos = _startpos_e_ in
            
# 87 "parser.mly"
                   (
    [ Do { expr = e ; pos = _startpos} ]
  )
# 1477 "parser.ml"
             in
            _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
        | Lseq ->
            _menhir_run44 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsge ->
            _menhir_run42 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsgt ->
            _menhir_run40 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsle ->
            _menhir_run38 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lslt ->
            _menhir_run36 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsne ->
            _menhir_run34 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run22 _menhir_env (Obj.magic _menhir_stack) _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | _ ->
        _menhir_fail ()

and _menhir_run9 : _menhir_env -> 'ttv_tail -> _menhir_state -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lpardeb ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_env = _menhir_discard _menhir_env in
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lbool _v ->
            _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState10 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lint _v ->
            _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState10 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lstr _v ->
            _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState10 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState10 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lvar _v ->
            _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState10 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState10)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_run52 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 10 "parser.mly"
       (string)
# 1538 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lassign ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
        let _menhir_stack = (_menhir_stack, _startpos) in
        let _menhir_env = _menhir_discard _menhir_env in
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lbool _v ->
            _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState53 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lint _v ->
            _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState53 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lstr _v ->
            _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState53 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState53 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lvar _v ->
            _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState53 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState53)
    | Lpardeb ->
        _menhir_run12 _menhir_env (Obj.magic _menhir_stack)
    | Ladd | Land | Ldiv | Lmul | Lor | Lrem | Lsc | Lseq | Lsge | Lsgt | Lsle | Lslt | Lsne | Lsub ->
        _menhir_reduce10 _menhir_env (Obj.magic _menhir_stack)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_run56 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 9 "parser.mly"
       (Ast.type_t)
# 1580 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lvar _v ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
        let _menhir_stack = (_menhir_stack, _v, _startpos) in
        let _menhir_env = _menhir_discard _menhir_env in
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lassign ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
            let _menhir_stack = (_menhir_stack, _startpos) in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | Lbool _v ->
                _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState59 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lint _v ->
                _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState59 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lstr _v ->
                _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState59 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lsub ->
                _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState59 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lvar _v ->
                _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState59 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState59)
        | Lsc ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
            let _menhir_env = _menhir_discard _menhir_env in
            let _menhir_stack = Obj.magic _menhir_stack in
            let _startpos__3_ = _startpos in
            let ((_menhir_stack, _menhir_s, (t : (
# 9 "parser.mly"
       (Ast.type_t)
# 1624 "parser.ml"
            )), _startpos_t_), (v : (
# 10 "parser.mly"
       (string)
# 1628 "parser.ml"
            )), _startpos_v_) = _menhir_stack in
            let _v : (Ast.Syntax.instr list) = let _startpos = _startpos_t_ in
            
# 71 "parser.mly"
                               (
    [ Decl { name = v ; type_t = t ; pos = _startpos } ]
  )
# 1636 "parser.ml"
             in
            _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let ((_menhir_stack, _menhir_s, _, _), _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_run13 : _menhir_env -> 'ttv_tail -> _menhir_state -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lint _v ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
        let _menhir_env = _menhir_discard _menhir_env in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (n : (
# 6 "parser.mly"
       (int)
# 1666 "parser.ml"
        )) = _v in
        let _startpos_n_ = _startpos in
        let (_menhir_stack, _menhir_s, _startpos__1_) = _menhir_stack in
        let _startpos = _startpos__1_ in
        let _v : (Ast.Syntax.expr) = let _startpos = _startpos__1_ in
        
# 108 "parser.mly"
                    (
    Val { value = Int (-n) ; pos = _startpos }
  )
# 1677 "parser.ml"
         in
        _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_run15 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 8 "parser.mly"
       (string)
# 1690 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let (s : (
# 8 "parser.mly"
       (string)
# 1698 "parser.ml"
    )) = _v in
    let _startpos_s_ = _startpos in
    let _startpos = _startpos_s_ in
    let _v : (Ast.Syntax.expr) = let _startpos = _startpos_s_ in
    
# 123 "parser.mly"
             (
    Val { value = Str (s) ; pos = _startpos }
  )
# 1708 "parser.ml"
     in
    _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos

and _menhir_run62 : _menhir_env -> 'ttv_tail -> _menhir_state -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState62 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState62 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsc ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_s = MenhirState62 in
        let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
        let _menhir_env = _menhir_discard _menhir_env in
        let _menhir_stack = Obj.magic _menhir_stack in
        let _startpos__2_ = _startpos in
        let (_menhir_stack, _menhir_s, _startpos__1_) = _menhir_stack in
        let _v : (Ast.Syntax.instr list) = let _startpos = _startpos__1_ in
        
# 65 "parser.mly"
                  (
    [ Return { expr = Val { value = Void ; pos = _startpos__2_ }
             ; pos = _startpos } ]
    )
# 1737 "parser.ml"
         in
        _menhir_goto_instr _menhir_env _menhir_stack _menhir_s _v
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState62 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState62 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState62 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState62

and _menhir_run16 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 6 "parser.mly"
       (int)
# 1754 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let (n : (
# 6 "parser.mly"
       (int)
# 1762 "parser.ml"
    )) = _v in
    let _startpos_n_ = _startpos in
    let _startpos = _startpos_n_ in
    let _v : (Ast.Syntax.expr) = let _startpos = _startpos_n_ in
    
# 113 "parser.mly"
             (
    Val { value = Int (n) ; pos = _startpos }
  )
# 1772 "parser.ml"
     in
    _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos

and _menhir_run66 : _menhir_env -> 'ttv_tail -> _menhir_state -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lpardeb ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_env = _menhir_discard _menhir_env in
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lbool _v ->
            _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState67 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lint _v ->
            _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState67 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lstr _v ->
            _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState67 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState67 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lvar _v ->
            _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState67 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState67)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_run70 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _v : (Ast.Syntax.block) = 
# 57 "parser.mly"
              ( [] )
# 1815 "parser.ml"
     in
    _menhir_goto_block _menhir_env _menhir_stack _menhir_s _v

and _menhir_run71 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_stack = (_menhir_stack, _menhir_s) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lbool _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lbracedeb ->
        _menhir_run71 _menhir_env (Obj.magic _menhir_stack) MenhirState71
    | Lbracefin ->
        _menhir_run70 _menhir_env (Obj.magic _menhir_stack) MenhirState71
    | Lif ->
        _menhir_run66 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lint _v ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lreturn ->
        _menhir_run62 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lstr _v ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lsub ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Ltype _v ->
        _menhir_run56 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lvar _v ->
        _menhir_run52 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | Lwhile ->
        _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState71 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState71

and _menhir_run17 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 7 "parser.mly"
       (bool)
# 1855 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let (b : (
# 7 "parser.mly"
       (bool)
# 1863 "parser.ml"
    )) = _v in
    let _startpos_b_ = _startpos in
    let _startpos = _startpos_b_ in
    let _v : (Ast.Syntax.expr) = let _startpos = _startpos_b_ in
    
# 118 "parser.mly"
              (
    Val { value = Bool (b) ; pos = _startpos }
  )
# 1873 "parser.ml"
     in
    _menhir_goto_expr _menhir_env _menhir_stack _menhir_s _v _startpos

and _menhir_goto_separated_nonempty_list_Lcomma_arg_ : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.args) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    match _menhir_s with
    | MenhirState3 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (x : (Ast.Syntax.args)) = _v in
        let _v : (Ast.Syntax.args) = 
# 144 "<standard.mly>"
    ( x )
# 1887 "parser.ml"
         in
        _menhir_goto_loption_separated_nonempty_list_Lcomma_arg__ _menhir_env _menhir_stack _menhir_s _v
    | MenhirState83 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (xs : (Ast.Syntax.args)) = _v in
        let (_menhir_stack, _menhir_s, (x : (Ast.Syntax.arg))) = _menhir_stack in
        let _v : (Ast.Syntax.args) = 
# 243 "<standard.mly>"
    ( x :: xs )
# 1898 "parser.ml"
         in
        _menhir_goto_separated_nonempty_list_Lcomma_arg_ _menhir_env _menhir_stack _menhir_s _v
    | _ ->
        _menhir_fail ()

and _menhir_fail : unit -> 'a =
  fun () ->
    Printf.eprintf "Internal failure -- please contact the parser generator's developers.\n%!";
    assert false

and _menhir_goto_loption_separated_nonempty_list_Lcomma_arg__ : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.args) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    let _menhir_stack = Obj.magic _menhir_stack in
    assert (not _menhir_env._menhir_error);
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lparfin ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_env = _menhir_discard _menhir_env in
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lbool _v ->
            _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lbracedeb ->
            _menhir_run71 _menhir_env (Obj.magic _menhir_stack) MenhirState8
        | Lbracefin ->
            _menhir_run70 _menhir_env (Obj.magic _menhir_stack) MenhirState8
        | Lif ->
            _menhir_run66 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lint _v ->
            _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lreturn ->
            _menhir_run62 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lstr _v ->
            _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lsub ->
            _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Ltype _v ->
            _menhir_run56 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lvar _v ->
            _menhir_run52 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | Lwhile ->
            _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState8 _menhir_env._menhir_lexbuf.Lexing.lex_start_p
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState8)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_run4 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 9 "parser.mly"
       (Ast.type_t)
# 1957 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lvar _v ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
        let _menhir_env = _menhir_discard _menhir_env in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (v : (
# 10 "parser.mly"
       (string)
# 1972 "parser.ml"
        )) = _v in
        let _startpos_v_ = _startpos in
        let (_menhir_stack, _menhir_s, (t : (
# 9 "parser.mly"
       (Ast.type_t)
# 1978 "parser.ml"
        )), _startpos_t_) = _menhir_stack in
        let _v : (Ast.Syntax.arg) = 
# 47 "parser.mly"
                         ( Arg { type_t = t ; name = v } )
# 1983 "parser.ml"
         in
        let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lcomma ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | Ltype _v ->
                _menhir_run4 _menhir_env (Obj.magic _menhir_stack) MenhirState83 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState83)
        | Lparfin ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, (x : (Ast.Syntax.arg))) = _menhir_stack in
            let _v : (Ast.Syntax.args) = 
# 241 "<standard.mly>"
    ( [ x ] )
# 2007 "parser.ml"
             in
            _menhir_goto_separated_nonempty_list_Lcomma_arg_ _menhir_env _menhir_stack _menhir_s _v
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_goto_prog : _menhir_env -> 'ttv_tail -> _menhir_state -> (Ast.Syntax.prog) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    match _menhir_s with
    | MenhirState0 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_1 : (Ast.Syntax.prog)) = _v in
        Obj.magic _1
    | MenhirState87 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (b : (Ast.Syntax.prog)) = _v in
        let (_menhir_stack, _menhir_s, (f : (Ast.Syntax.def list))) = _menhir_stack in
        let _v : (Ast.Syntax.prog) = 
# 30 "parser.mly"
                       ( f @ b )
# 2039 "parser.ml"
         in
        _menhir_goto_prog _menhir_env _menhir_stack _menhir_s _v
    | _ ->
        _menhir_fail ()

and _menhir_errorcase : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    match _menhir_s with
    | MenhirState87 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState83 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState78 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState72 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState71 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState69 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState67 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState62 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState59 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (((_menhir_stack, _menhir_s, _, _), _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState53 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState51 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState48 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState46 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState44 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState42 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState40 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState38 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState36 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState34 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState32 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState30 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState28 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState26 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState24 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState22 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState12 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState10 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState8 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState3 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, _, _), _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState0 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        raise _eRR

and _menhir_run1 : _menhir_env -> 'ttv_tail -> _menhir_state -> (
# 9 "parser.mly"
       (Ast.type_t)
# 2171 "parser.ml"
) -> Lexing.position -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v _startpos ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v, _startpos) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lvar _v ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
        let _menhir_stack = (_menhir_stack, _v, _startpos) in
        let _menhir_env = _menhir_discard _menhir_env in
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | Lpardeb ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | Ltype _v ->
                _menhir_run4 _menhir_env (Obj.magic _menhir_stack) MenhirState3 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
            | Lparfin ->
                let _menhir_stack = Obj.magic _menhir_stack in
                let _menhir_s = MenhirState3 in
                let _v : (Ast.Syntax.args) = 
# 142 "<standard.mly>"
    ( [] )
# 2198 "parser.ml"
                 in
                _menhir_goto_loption_separated_nonempty_list_Lcomma_arg__ _menhir_env _menhir_stack _menhir_s _v
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState3)
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let ((_menhir_stack, _menhir_s, _, _), _, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_run85 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_stack = Obj.magic _menhir_stack in
    let _v : (Ast.Syntax.prog) = 
# 32 "parser.mly"
         ( [] )
# 2224 "parser.ml"
     in
    _menhir_goto_prog _menhir_env _menhir_stack _menhir_s _v

and _menhir_discard : _menhir_env -> _menhir_env =
  fun _menhir_env ->
    let lexer = _menhir_env._menhir_lexer in
    let lexbuf = _menhir_env._menhir_lexbuf in
    let _tok = lexer lexbuf in
    {
      _menhir_lexer = lexer;
      _menhir_lexbuf = lexbuf;
      _menhir_token = _tok;
      _menhir_error = false;
    }

and prog : (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.Syntax.prog) =
  fun lexer lexbuf ->
    let _menhir_env = {
      _menhir_lexer = lexer;
      _menhir_lexbuf = lexbuf;
      _menhir_token = Obj.magic ();
      _menhir_error = false;
    } in
    Obj.magic (let _menhir_stack = ((), _menhir_env._menhir_lexbuf.Lexing.lex_curr_p) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | Lend ->
        _menhir_run85 _menhir_env (Obj.magic _menhir_stack) MenhirState0
    | Ltype _v ->
        _menhir_run1 _menhir_env (Obj.magic _menhir_stack) MenhirState0 _v _menhir_env._menhir_lexbuf.Lexing.lex_start_p
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState0)

# 269 "<standard.mly>"
  

# 2264 "parser.ml"

open Lexing

let err msg pos =
	Printf.eprintf "Error on line %d col %d: %s.\n"
		pos.pos_lnum (pos.pos_cnum - pos.pos_bol) msg ;
	exit 1

let () =
	if (Array.length Sys.argv) != 2 then begin
			Printf.eprintf "Usage: %s <file>\n" Sys.argv.(0) ;
			exit 1
		end;
	let f = open_in Sys.argv.(1) in
	let buf = Lexing.from_channel f in
	try
		let syntax = Parser.block Lexer.token buf in
		close_in f ;
		let ir = Semantics.analyze syntax in
		let res = Interp.eval ir in
		Printer.print_value res ;
		print_newline ()
	with
	| Lexer.Error c ->
		 err (Printf.sprintf "unrecognized char '%c'" c) (Lexing.lexeme_start_p buf)
	| Parser.Error ->
		 err "syntax error" (Lexing.lexeme_start_p buf)
	| Semantics.Error (msg, pos) -> err msg pos

nombre(Z) :- member(Z,[1,2,3,4]).
nombre(X) :- member(X,[1,2,3,4,5]).

diff(_,[]).
diff(Z,[L|Ls]) :- Z \= L, diff(Z,Ls).
diff([]).
diff([L|Ls]) :- diff(L,Ls), diff(Ls).

print_each_sudoku([A,B,C,D]) :- nombre(A), nombre(B), nombre(C), nombre(D), diff([A,B,C,D]).
print_each_sudoku([A,B,C,D,E]) :- nombre(A), nombre(B), nombre(C), nombre(D), nombre(E), diff([A,B,C,D,E]).

print_line_sudoku(A,B,C,D,_) :- write(A), write(" "), write(B), write(" "), write(C), write(" "), write(D), write("\n").

sudoku([A1,A2,A3,A4,A5,B1,B2,B3,B4,B5,C1,C2,C3,C4,C5,D1,D2,D3,D4,D5]) :-  print_each_sudoku([A1,A2,A3,A4,A5]), print_each_sudoku([B1,B2,B3,B4,B5]), print_each_sudoku([C1,C2,C3,C4,C5]), print_each_sudoku([D1,D2,D3,D4,D5]), print_each_sudoku([_,_,_,_,_]), diff([A1,B1,C1,D1]), diff([A2,B2,C2,D2,_]), diff([A3,B3,C3,D3,_]), diff([A4,B4,C4,D4,_]), diff([A5,B5,C5,D5,_]), diff([A1,A2,B1,B2,C2]), diff([C1,D1,_,_,_]), diff([D5,C5,B5,_,_]), diff([A3,A4,A5,B3,B4]), diff([C3,C4,D2,D3,D4]), print_line_sudoku(A1,A2,A3,A4,A5), print_line_sudoku(B1,B2,B3,B4,B5), print_line_sudoku(C1,C2,C3,C4,C5), print_line_sudoku(D1,D2,D3,D4,D5).
sudoku2([A1,A2,A3,A4,A5,B1,B2,B3,B4,B5,C1,C2,C3,C4,C5,D1,D2,D3,D4,D5,E1,E2,E3,E4,E5]) :-  print_each_sudoku([A1,A2,A3,A4,A5]), print_each_sudoku([B1,B2,B3,B4,B5]), print_each_sudoku([C1,C2,C3,C4,C5]), print_each_sudoku([D1,D2,D3,D4,D5]), print_each_sudoku([E1,E2,E3,E4,E5]), diff([A1,B1,C1,D1,E1]), diff([A2,B2,C2,D2,E2]), diff([A3,B3,C3,D3,E3]), diff([A4,B4,C4,D4,E4]), diff([A5,B5,C5,D5,E5]), diff([A1,A2,B1,B2,C2]), diff([C1,D1,E1,E2,E3]), diff([E4,E5,D5,C5,B5]), diff([A3,A4,A5,B3,B4]), diff([C3,C4,D2,D3,D4]), print_line_sudoku(A1,A2,A3,A4,A5), print_line_sudoku(B1,B2,B3,B4,B5), print_line_sudoku(C1,C2,C3,C4,C5), print_line_sudoku(D1,D2,D3,D4,D5), print_line_sudoku(E1,E2,E3,E4,E5).
all_sol_sudoku2() :- sudoku([_,3,2,_,_,_,1,_,_,2,_,_,1,_,_,1,_,_,2,_,_,_,3,1,_]), sudoku2([]).

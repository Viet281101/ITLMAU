print_l([A|B]).
print_l([A|B]):- write(A), write(''), print_l(B).


mkl(X,1,[X]).
mkl(X,N,[X|L]):-N>1, N1 is N-1, mkl(X,N1,L).

l_2l([],[]).
l_2l([C|D],X) :- l_2l(D,X1), mkl(C,2,X2), append(X2,X1,X).

l_3l([],[]).
l_3l([E|F],X) :- l_2l(F,X1), mkl(E,3,X2), append(X2,X1,X).


double_l([],[]).
double_l([G|H],X) :- double_l(H,X1), G1 is G * 2, mkl(G1,1,X2), append(X2,X1,X).

mkl([],0,_).
mkl([I|J],K,L) :-I == L,
          K1 is K - 1,
          mkl(J,K1,L).


taille([],0).
taille([_|M],N) :- taille(M,N1),
            N is 1 + N1.

sum([],0).
sum([O|P],Q) :- sum(P, Q1), Q is Q1 + O.

sum2([],0).
sum2([O|P],Q) :- sum2(P, Q2),  Q is Q2 + O*O .

avg([],0).
avg([O|P],Q) :- sum([O|P],Q3), taille([O|P],Q4), Q is Q3//Q4.



is_list_l([A|B]).
is_list_l([_|Ls]) :- is_list(Ls).
isflat([A],[B]).
isflat([A|As],X) :- is_list(A), isflat(A,X1), isflat(As,X2), append(X1,X2,X).
isflat([A|As],X) :- not(is_list(A)), isflat(As,X1), mkl(A,1,X2), append(X2,X1,X).




flatten2([], []).
flatten2([L | L2], X) :- flatten2(L, L3), flatten2(L2, L4), append(L3, L4, X).
flatten2(L, [L]).

isflat([], []).
isflat([A | B], L) :- flatten2(A, L1), isflat(B, L2), append(L1, L2, L).

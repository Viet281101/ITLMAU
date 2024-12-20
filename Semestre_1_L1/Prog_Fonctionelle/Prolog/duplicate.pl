mklist(x,1,[X]).
mklist(X,N,[X|L]):- N>1, N1 is N-1, mklist(X,N1,L).

duplicate([],_,[]).
duplicate([A|B],N,X):- duplicate(B,N,X1), mklist(A,N,X2), append(X2,X1,X).

dupicate([A,B],X):-duplicate(A,B,X).

duplicate([[],_],[]).
duplicate([A,B],R):-A=[T|Q], mklist(T,B,T1), duplicate([Q,B],Q1), append(T1,Q1,R).

rotate_left(_,0,X):-write(X).
rotate_left([A|B], N, C):- N>0, append(B, [A], X), N1 is N-1, rotate_left(X, N1, C).

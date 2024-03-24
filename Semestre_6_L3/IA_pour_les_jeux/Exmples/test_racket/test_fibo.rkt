#lang datalog
fibo(0, 0).
fibo(1, 1).
fibo(N, F):- N != 1, N != 0, N1:- -(N, 1), N2 :- -(N, 2),
	fibo(N1, F1), fibo(N2, F2), F:- +(F1, F2).
fibo(30, F)?
fibo(12, F)?
jeu(T, M) :- T=<0, write('fini').
jeu(T, M) :- T>0, affiche(T), random(X), tir(T, M, X).

evaluer_etat(T, M, X).
tirage(T, M, X) :- X>=0.5, T1 is T - M, jeu(T1, M).
tirage(T, M, X) :- X<0.5, T1 is T + M, jeu(T1, M).
next_etat(T) :- write('je joue avec '), write(T), nl.




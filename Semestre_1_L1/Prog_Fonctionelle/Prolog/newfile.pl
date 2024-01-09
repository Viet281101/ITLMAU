p(a).
p(b).
p(c).
q(1,a).
r1(X) :- p(X),q(1,X).
r2(X) :- q(1,X), p(X).


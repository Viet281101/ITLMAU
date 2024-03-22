#lang datalog
a(X,Y):- Y:- +(X,1).
b(X,Y):- Y:- -(X,1).
c(X,Y):- Y:-*(X,2).
d(X,Y):- Y:- /(X,2).
e(X,Y):- d(X,Y1), Y2:- >(Y1,1), Y2=true, Y=1.
f(X,Y):- Y:- log(X).
g(X,Y):- Y:- sqrt(X).
h(X,Y):- Y:- expt(X,3).
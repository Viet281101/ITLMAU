#TP6:

import sys
from pyDatalog import pyDatalog

def printf(format, *args):
  sys.stdout.write(format % args)
id = 0
if(len(sys.argv) == 2): id = int(sys.argv[1])

if id==1:
  pyDatalog.create_terms('X')
  print(X.in_(range(1,11)).data)

if id==2:
  pyDatalog.create_terms('X,Y')
  print(((X.in_(range(1,6,1))) & (Y.in_(range(-1,-6,-1)))).data)

if id==3:
  pyDatalog.create_terms('X,Y')
  print(((X.in_(range(1,6))) & (Y.in_(range(-1,-6,-1))) & (X+Y==0)).data)

if id==4:
  pyDatalog.create_terms('even, N, N1')
  + even(0)
  even(N) <= (N>0) & (N1==N-2) & even(N1)
  print(even(20)==[()])
  print(even(21)==[()])  

if id==5:
  pyDatalog.create_terms('X,Y')
  pyDatalog.create_terms('even, N, N1')
  + even(0)
  even(N) <= (N>0) & (N1==N-2) & even(N1)
  print(((X.in_(range(1,6))) & (Y.in_(range(1,6))) & even(X+Y)).data)
  
if id==6:
  pyDatalog.create_terms('X,Y,Z')
  pyDatalog.create_terms('even, N, N1')
  + even(0)
  even(N) <= (N>0) & (N1==N-2) & even(N1)
  even(X,Y,Z) <= (X+Y==N) & even(N+Z)
  print(((X.in_(range(1,4))) & (Y.in_(range(1,4))) & (Z.in_(range(1,4))) & even(X,Y,Z)).data)
  
if id==7:
  pyDatalog.create_terms('X,Y,Z,N')
  pyDatalog.create_terms('sum3')
  sum3(X,Y,Z) <= (X.in_(range(1,10)))&(Y.in_(range(1,10)))&(Z.in_(range(1,10)))&	\(X!=Y)&(X!=Z)&(Y!=Z)&(X+Y==N)&(N+Z==15)
  print(sum3(1,2,3))
  print((X==1)&(Y==2)&(Z==3)&(sum3(X,Y,Z)))
  print(sum3(4,5,6))
  print((X==4)&(Y==5)&(Z==6)&(sum3(X,Y,Z)))

if id==8:
  pyDatalog.create_terms('X,Y,Z,N')
  pyDatalog.create_terms('sum3')
  sum3(X,Y,Z) <= ((X.in_(range(1,10)))&(Y.in_(range(1,10)))&(Z.in_(range 1,10)))&	(X!=Y)&(X!=Z)&(Y!=Z)&(X+Y==N)&(N+Z==15))
  pyDatalog.create_terms('X0,X1,X2,X3,X4,X5,X6,X7,X8')
  pyDatalog.creata_terms('cm3x3')
  cm3x3((X0,X1,X2,X3,X4,X5,X6,X7,X8)) <= (
	sum3(X0,X1,X2) & sum3(X3,X4,X5) & sum3(X6,X7,X8)& 
	sum3(X0,X3,X6) & sum3(X1,X4,X7) & sum3(X2,X5,X8)&
	sum3(X0,X4,X8) & sum3(X2,X4,X6))
  print(cm3x3((2,X0,X1,X2,5,X3,X4,X5,8)))

if id==9:
  pyDatalog.create_terms('X,Y,Z,N')
  pyDatalog.create_terms('sum3')
  sum3(X,Y,Z) <= (X.in_(range(1,10)))&(Y.in_(range(1,10)))&(Z.in_(range(1,10)))&	\(X!=Y)&(X!=Z)&(Y!=Z)&(X+Y==N)&(N+Z==15)
  pyDatalog.create_terms('X0,X1,X2,X3,X4,X5,X6,X7,X8')
  pyDatalog.creata_terms('cm3x3')
  cm3x3((X0,X1,X2,X3,X4,X5,X6,X7,X8)) <= \
	sum3(X0,X1,X2) & sum3(X3,X4,X5) & sum3(X6,X7,X8)& \
	sum3(X0,X3,X6) & sum3(X1,X4,X7) & sum3(X2,X5,X8)& \
	sum3(X0,X4,X8) & sum3(X2,X4,X6)
  print(cm3x3(X))
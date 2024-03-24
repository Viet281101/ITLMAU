#lang datalog/sexp
(! (integer_sum 1 1))
(! (:- (integer_sum X Y)(!= X 1) 
    (- X 1 :- X1) (integer_sum X1 R1) (+ X R1 :- Y)
    ))
(? (integer_sum 10 X))
(? (integer_sum 100 X))
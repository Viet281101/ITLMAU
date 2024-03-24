#lang datalog/sexp
(! (:- (is_even X Y)
    (modulo X 2 :- X1) (= X1 0) (= Y true)
    ))
(! (:- (is_even X Y)
    (modulo X 2 :- X1) (= X1 1) (= Y false)
    ))
(? (is_even 10 Y))
(? (is_even 11 Y))
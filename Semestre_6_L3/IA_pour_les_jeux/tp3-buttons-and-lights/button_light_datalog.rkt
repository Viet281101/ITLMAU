
#lang datalog/sexp

(! (init-lights 0 0 0))

(! (toggle-light 0 0 0 1 0 0))
(! (toggle-light 0 1 0 0 1 0))
(! (toggle-light 0 0 1 0 0 1))

(? (current-lights X Y Z))


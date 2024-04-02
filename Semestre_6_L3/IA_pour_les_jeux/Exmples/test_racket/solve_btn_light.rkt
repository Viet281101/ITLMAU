#lang racket

(define (toggle-light light)
	(if (= light 0) 1 0))

(define (move-lights state button-pressed)
	(match button-pressed
		['a (list (toggle-light (first state)) (second state) (third state))]
		['b (list (toggle-light (first state)) (toggle-light (second state)) (third state))]
		['c (list (first state) (toggle-light (second state)) (toggle-light (third state)))]))

(define (game-solved? state)
	(and (= (first state) 1) (= (second state) 1) (= (third state) 1)))

(define (solve-game state moves)
	(if (game-solved? state)
		'solved
		(if (null? moves)
			'unsolved
			(solve-game (move-lights state (first moves)) (rest moves)))))

(solve-game '(0 0 0) '(a b c))
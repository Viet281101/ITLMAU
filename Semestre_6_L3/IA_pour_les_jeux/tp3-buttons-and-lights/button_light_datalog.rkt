#lang racket
(require datalog)

(define lights-theory (make-theory))

(datalog! lights-theory
	(! (state 0 0 0 0 '()))
)

(datalog! lights-theory
	(! (:- (state (not A) B C (- T 1) (cons 'a L))
			(state A B C T L)
			(not (= T 0))))
	(! (:- (state A (not B) A (- T 1) (cons 'b L))
			(state A B C T L)
			(not (= T 0))))
	(! (:- (state A B (not C) (- T 1) (cons 'c L))
			(state A B C T L)
			(not (= T 0))))
)

(define (show-lights)
	(for ([result (in-list (datalog lights-theory (? (state A B C _ _))))])
		(printf "Light states: ~a ~a ~a\n" A B C)))

(define (run-game)
	(let loop ()
		(printf "\nEnter command (a, b, c, show, quit): ")
		(let ([cmd (read-line)])
		(cond
			[(string=? cmd "quit") (exit)]
			[(string=? cmd "show") (show-lights)]
			[(string=? cmd "a") (apply-action 'a)]
			[(string=? cmd "b") (apply-action 'b)]
			[(string=? cmd "c") (apply-action 'c)]
			[else (printf "Unknown command.\n")])
		(loop))))

(define (apply-action action)
	(let ([current-state (first (datalog lights-theory (? (state _ _ _ _ _))))])
		(define new-state
		(case action
			[('a) (list (not (first current-state))
						(second current-state)
						(third current-state)
						(sub1 (fourth current-state))
						(cons 'a (fifth current-state)))]
			[('b) (list (first current-state)
						(not (second current-state))
						(first current-state)
						(sub1 (fourth current-state))
						(cons 'b (fifth current-state)))]
			[('c) (list (first current-state)
						(second current-state)
						(not (third current-state))
						(sub1 (fourth current-state))
						(cons 'c (fifth current-state)))]))
		(datalog! lights-theory
		(! (apply new-state)))
		(check-win)))

(define (apply new-state)
	(datalog! lights-theory
		(! (state (first new-state)
				(second new-state)
				(third new-state)
				(fourth new-state)
				(fifth new-state)))))


(run-game)


(datalog! lights-theory
	(! (:- (win)
			(state 1 1 1 _ _))))

(define (check-win)
	(for ([result (in-list (datalog lights-theory (? (state 1 1 1 _ _))))])
		(printf "Congratulations! You have won the game!\n")
		(exit)))


(check-win)


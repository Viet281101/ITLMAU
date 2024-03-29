#lang racket

(define lights '(0 0 0))

(define (toggle-light lst pos)
	(for/list ([i (in-range (length lst))])
		(if (= i pos)
			(if (= (list-ref lst i) 0) 1 0)
			(list-ref lst i))))

(define (display-lights lst)
	(for ([i (in-list lst)])
		(printf "~a " (if (= i 0) "Off" "On")))
	(newline))

(define (run-game)
	(let loop ([current-lights lights])
		(display-lights current-lights)
		(printf "Sélectionnez la lumière pour inverser le statut (0-2): ")
		(let ([input (read)])
		(when (and (integer? input) (>= input 0) (<= input 2))
			(let ([new-lights (toggle-light current-lights input)])
			(loop new-lights))))))

(run-game)

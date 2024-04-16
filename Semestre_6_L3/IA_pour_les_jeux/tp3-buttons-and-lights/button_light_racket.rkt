
#lang racket

(define lights '(0 0 0))
(define player-name (make-parameter ""))
(define game-active (make-parameter #f))

(define (toggle-light lst pos)
	(cond [(= pos 0) (list (if (= (first lst) 0) 1 0) (second lst) (third lst))]
			[(= pos 1) (list 0 (if (= (first lst) 0) 0 1) (third lst))]
			[(= pos 2) (list (first lst) 0 (if (= (second lst) 0) 0 1))]))

(define (display-lights lst)
	(for ([i (in-list lst)])
		(printf "~a " (if (= i 0) "Off" "On")))
	(newline))

(define (game-won? lst)
	(andmap (lambda (light) (= light 1)) lst))

(define (random-move)
	(random 3))

(define (apply-random-move current-lights)
	(let ([move (random-move)])
		(case move
		[(0) (toggle-light current-lights 0)]
		[(1) (list 0 (if (= (first current-lights) 0) 0 1) (third current-lights))]
		[(2) (list (first current-lights) 0 (if (= (second current-lights) 0) 0 1))])))

(define (try-moves current-lights moves remaining-moves)
	(if (= remaining-moves 0)
		(if (game-won? current-lights)
			(list moves)
			'())
		(append
		(try-moves (toggle-light current-lights 0) (append moves '(a)) (- remaining-moves 1))
		(try-moves (list 0 (if (= (first current-lights) 0) 0 1) (third current-lights))
					(append moves '(b)) (- remaining-moves 1))
		(try-moves (list (first current-lights) 0 (if (= (second current-lights) 0) 0 1))
					(append moves '(c)) (- remaining-moves 1)))))

(define (eval current-lights remaining-moves)
	(try-moves current-lights '() remaining-moves))

(define (simulate-actions initial-lights actions)
	(define (apply-action state action)
		(case action
		[('a) (toggle-light state 0)]
		[('b) (list 0 (if (= (first state) 0) 0 1) (third state))]
		[('c) (list (first state) 0 (if (= (second state) 0) 0 1))]))
	(foldl apply-action initial-lights actions))

(define (run-game)
	(printf "Welcome to Lights and Buttons Game!\nCommands: setname <...>, name, newgame, play <1-3>, randmove, solve, show, quit\n")
	(let loop ([current-lights lights])
		(printf "\nEnter command: ")
		(let ([cmd (read-line)])
		(cond
			[(string=? cmd "quit") (exit)]
			[(string-prefix? cmd "setname ")
			(let ([name (string-trim (substring cmd 8))])
			(player-name name)
			(printf "Player name set to: ~a\n\n" (player-name)))]
			[(string=? cmd "name")
			(if (string=? (player-name) "")
				(printf "No player name set. Please use the 'setname <name>' command.\n\n")
				(printf "Current player name: ~a\n\n" (player-name)))]
			[(string=? cmd "newgame")
			(if (string=? (player-name) "")
				(printf "Please set a player name using setname command.\n\n")
				(begin
				(set! current-lights '(0 0 0))
				(game-active #t)
				(printf "New game started. You can set light with command: play <1-3> or randmove\n\n")
				(display-lights current-lights)))]
			[(string-prefix? cmd "play ")
			(if (not (game-active))
				(printf "Game has not started. Please use newgame to start.\n\n")
				(let* ([pos (string->number (substring cmd 5))]
						[new-lights (toggle-light current-lights (- pos 1))])
				(set! current-lights new-lights)
				(printf "Light set! \n\n")
				(display-lights new-lights)
				(when (game-won? new-lights)
					(printf "\nPlayer ~a wins!\n" (player-name))
					(game-active #f))))]
			[(string=? cmd "randmove")
			(if (not (game-active))
				(printf "Game has not started. Please use newgame to start.\n\n")
				(let ([new-lights (apply-random-move current-lights)])
				(set! current-lights new-lights)
				(printf "Random move applied.\n\n")
				(display-lights new-lights)
				(when (game-won? new-lights)
					(printf "Player ~a wins!\n" (player-name))
					(game-active #f))))]
			[(string=? cmd "solve")
			(let ([solution (eval current-lights 7)])
			(if (null? solution)
				(printf "No solution found.\n\n")
				(begin
					(printf "Solution: ~a\n\n" solution)
					(for-each (lambda (sol)
								(let ([result (simulate-actions '(0 0 0) sol)])
								(printf "Testing solution ~a: Final state ~a\n" sol result)))
							solution))))]
			[(string=? cmd "show")
			(if (game-active)
				(display-lights current-lights)
				(printf "Game has not started. Please use newgame to start.\n\n"))]
			[else (printf "Unknown command.\n\n")])
		(loop current-lights))))

(run-game)

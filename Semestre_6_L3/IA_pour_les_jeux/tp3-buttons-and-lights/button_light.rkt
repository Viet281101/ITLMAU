
#lang racket

(require datalog)

(define db (datalog-db))

(datalog! db
	(state 0 0 0))

(define (query-state db)
	(datalog db
		(:- (q ?a ?b ?c)
			(state ?a ?b ?c))))

(for ([result (in-list (query-state db))])
	(displayln result))


(load "max_subsequence.scm")

;; Testing lib

(define (assert-eq actual expected)
  (let ((act (eval actual))
	(exp (eval expected)))
	(if (equal? act exp) (list #t)
	    (list #f actual expected act exp))))

(define (is-list-tests args)
  (cond ((null? args) #f)
	((equal? "--list_tests" (car args)) #t)
	(else (is-list-tests (cdr args)))))

(define (is-run-test args)
  (cond ((null? args) #f)
	((string-prefix? "--run_test=" (car args)) (substring (car args) (string-length "--run_test=") (length (car args))))
	(else (is-run-test (cdr args)))))

(define (is-score args)
  (cond ((null? args) #f)
	((string-prefix? "--results_file=" (car args)) (substring (car args) (string-length "--results_file=") (length (car args))))
	(else (is-score (cdr args)))))

(define (assign-weights weight tests)
  (if (null? tests) '()
      (cons (list (caar tests) weight (cadr (car tests)))
	      (assign-weights weight (cdr tests)))))

(define (extract-suite-tests suite)
  (assign-weights (/ (car suite) (length (cadr suite)))
		  (cadr suite)))

(define (extract-tests suites)
  (if (null? suites) '()
      (append (extract-suite-tests (car suites))
	      (extract-tests (cdr suites)))))

(define (extract-names tests)
  (map car tests))

(define (run-test test)
  (display "TESTING: ")
  (display (car test))
  (newline)
  (let ((res (apply assert-eq (caddr test))))
    (if (not (car res))
	(begin
	  (display "Expected: ")
	  (display (car (cddddr res)))
	  (display " Got: ")
	  (display (cadddr res))
	  (newline)))
    (display "TEST ")
    (display (car test))
    (display (if (car res) ": SUCCESS" ": FAILURE"))
    (newline)
    (car res)))

(define (run-tests tests)
  (map run-test tests))

(define (filter expr seq)
  (cond ((null? seq) '())
	((expr (car seq)) (cons (car seq) (filter expr (cdr seq))))
	(else (filter expr (cdr seq)))))

(define (find-test name tests)
  (filter (lambda (test) (equal? name (car test))) tests))

(define (display-names tests)
  (map (lambda (name) (display name)(newline))
       (extract-names tests))
  #t)

(define (read-all-lines in)
  (let ((line (read-line in)))
    (if (eof-object? line) '()
	(cons line (read-all-lines in)))))

(define (line->result line)
  (let ((items (string-split line " ")))
    (list (car items) (string->number (cadr items)))))

(define (lines->results lines)
  (if (null? lines) '()
      (cons (line->result (car lines)) (lines->results (cdr lines)))))

(define (read-results results-file)
  (define in (open-input-file results-file))
  (let ((results (lines->results (read-all-lines in))))
    (close-input-port in)
    results))

(define (calculate-score results-file tests)
  (apply + (map * (map cadr (read-results results-file))
		(map cadr tests))))

(define (process-tests args tests)
  (cond ((is-list-tests args) (display-names tests))
	((is-score args) (display (calculate-score (is-score args) tests)))
	((is-run-test args)
	 (eval (cons and (run-tests (find-test (is-run-test args) tests)))))
	(else (eval (cons and (run-tests tests))))))

;; End of testing lib

(define (generate-tests)
  (quasiquote
   (
      (1.0
       (
		("T-1" ((max-subsequence '(1 2 3 4 5) '(1 7 3 9 5 10)) 3))
		("T-2" ((max-subsequence '(1 2 3 4 5) '(1 3 2 3 5)) 4))
		("T-3" ((max-subsequence '(1 2 3 2 4) '(1 5 3 2 4)) 4))
		("T-4" ((max-subsequence '(1 2 3 2 4 5 6 7 8 9 10) '(101 102 103 104 105 106 107 108 109 110)) 0))
		("T-5" ((max-subsequence '(5 1 6 3 10 7 4 2 8 9) '(3 4 10 2 6 5 1 8 9 7)) 5))
		("T-6" ((max-subsequence '(3 1 5 6 4 10 2 7 8 9) '(4 9 1 3 5 8 6 10 2 7)) 6))
		("T-7" ((max-subsequence '(6 9 3 5 1 4 2 8 7 10) '(5 2 10 3 6 9 1 8 7 4)) 5))
		("T-8" ((max-subsequence '(9 4 10 3 5 6 2 8 7 1) '(4 1 8 7 3 6 9 10 5 2)) 4))
		("T-9" ((max-subsequence '(1 2 3 4 5 6 7 8 9 10) '(1 2 3 4 5 6 7 8 9 10)) 10))
		)
	   )
	  ;; (0.7
      ;;  (
	  ;; 	("T-6" ())
	  ;; 	("T-7" ())
	  ;; 	("T-8" ())
	  ;; 	("T-9" ())
	  ;; 	)
	  ;;  )
        )
      )
      )

(if (not (process-tests (vector->list command-line-arguments)
			(extract-tests (generate-tests))))
    (exit 1))

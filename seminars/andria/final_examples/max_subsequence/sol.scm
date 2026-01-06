(define (max-subsequence a b)
  (if (or (null? a) (null? b)) 0
	  (if (= (car a) (car b)) (+ 1 (max-subsequence (cdr a) (cdr b)))
		  (max (max-subsequence a (cdr b)) (max-subsequence (cdr a) b)))))

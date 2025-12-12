(define (digits number)
  (if (< number 10) (list number)
    (append (digits (div number 10)) (list (remainder number 10)))
  )
)

(define (list_power l)
  (map (lambda (n) (expt n (length l))) l)
)

(define (sum l)
  (if (null? l) 0
    (+ (car l) (sum (cdr l)))
  )
)

(define (narcisisstic? n)
  (= n 
        (sum (list_power (digits n)))
  )
)

(define (count n l)
  (cond ((null? l) 0)
        ((= (car l) n) (+ 1 (count n (cdr l))))
        (#t (count n (cdr l)))
  )
)

(define (set l)
  (cond ((null? l) '())
        ((= 0 (count (car l) (cdr l))) (cons (car l) (set (cdr l))))
        (#t (set (cdr l)))
  )
)

(define (frequency l)
  (map (lambda (n) (list n (count n l))) (set l))
)

(define (multiply_ elem n)
  (if (= n 0) '()
    (cons elem (multiply_ elem (- n 1)))
  )
)

(define (multiply n l)
  (apply append (map (lambda (e) (multiply_ e n)) l))
)

;a b c d e

(define (ksubset k l)
  (cond ((= 0 k) '(()))
    ((< (length l) k) '())
    ((append (map (lambda (e) (cons (car l) e)) (ksubset (- k 1) (cdr l)))
             (ksubset k (cdr l))
    ))
  )
)


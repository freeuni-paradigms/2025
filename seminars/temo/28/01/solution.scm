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

(define (narcisisstic? number)
  (= (sum (list_power (digits number))) number)
)

(define (count n l)
  (if (null? l) 0
    (if (= (car l) n) (+ 1 (count n (cdr l)))
      (count n (cdr l)))
  )
)

(define (set l)
  (cond ((null? l) '())
        ((= (count (car l) l) 1) (cons (car l) (set (cdr l))))
        (#t (set (cdr l)))
  )
)

(define (frequency l)
  (map (lambda (n) (list n (count n l))) (set l))
)

;2 '(1 2 1 2 2) 
;'(1 1 2 2 1 1 2 2 2 2)
(define (mult n e)
  (if (zero? n) '()
    (cons e (mult (- n 1) e))
  )
)

(define (multiply n l)
  (apply append (map (lambda (e) (mult n e)) l))
)

(define (ksubset k l)
  (cond ((zero? k) '(()))
        ((null? l) '())
        (else (append
              (map 
                (lambda (e) (cons (car l) e))
                (ksubset (- k 1) (cdr l)))
              (ksubset k (cdr l)))

        )
  )
)

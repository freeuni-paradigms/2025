(define (reverse_ l)
  (if (null? l) '()
    (append (reverse_ (cdr l)) (list (car l)))
  )
)

(define (sorted? l)
  (if (< (length l) 2) #t
      (and (< (car l) (cadr l)) (sorted? (cdr l)))
  )
)

(define (max_ l)
  (cond ((null? l) 0)
    ((< (car l) (max_ (cdr l))) (max_ (cdr l)))
    (#t (car l))
  )
)

(define (filter_ func l)
  (cond ((null? l) '())
        ((func (car l)) (cons (car l) (filter_ func (cdr l))))
        ((filter_ func (cdr l)))
  )
)

(define (divisible3 n)
  (= (remainder n 3) 0)
)

(define (max_divisible3 l)
  (max_ (filter_ divisible3 l))
)

(define (range k)
  (if (= k 1) '(1)
    (append (range (- k 1)) (list k))
  )
)

(define (pow n p)
  (if (= p 0) 1
    (* n (pow n (- p 1)))
  )
)

(define (generate_powers_helper n l)
  (if (null? l) '()
      (cons (pow n (car l)) (generate_powers_helper n (cdr l)))
  )
)

(define (generate_powers n k)
  (generate_powers_helper n (range k))
)

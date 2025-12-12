(define (first-elem l)
  (if (null? l)
    "None"
    (car l)
  )
)

(define (abs_ num)
  (if (< 0 num) num
    (- 0 num)
  )
)

(define (right-triangle l)
  (= (+ (* (car l) (car l)) (* (cadr l) (cadr l)))
     (* (caddr l) (caddr l))
  )
)

(define (last-elem l)
  (cond ((null? l) "None")
          ((= (length l) 1) (car l))
          ((last-elem (cdr l)))
  )
)

(define (length_ l)
  (if (null? l) 0
    (+ 1 (length_ (cdr l))) 
  )
)

(define (k-th-element l k)
  (cond ((null? l) "None")
        ((= k 0) (car l))
        ((k-th-element (cdr l) (- k 1)))
  )
)

(define (filter-range l a b)
  (if (null? l) '()
    (if (or (and (>= (car l) a) (<= (car l) b))
            (and (>= (car l) b) (<= (car l) a))
        )
            (cons (car l) (filter-range(cdr l) a b))
                                          (filter-range(cdr l) a b)
                                          )
    )
)



(define (prime-helper k n)
  (cond ((= n k) #t)
        ((> n k) #f)
        ((= (remainder k n) 0) #f)
        ((prime-helper k (+ n 1)))
  )
)

(define (prime? k)
  (prime-helper k 2) 
)

(define (primes? l)
  (if (null? l) '()
    (cons (prime? (car l)) (primes? (cdr l)))
  )
)



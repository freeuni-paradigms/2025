(define (reverse_ l)
  (if (null? l) '()
    (append (reverse_ (cdr l)) (list (car l)))
  )
)

; 1 2 3 4
; 2 3 4  1
; 3 4    2 1
; 4      3 2 1
;        4 3 2 1


(define (sorted? l)
  (cond ((< (length l) 2) #t)
         ((> (car l) (cadr l)) #f)
         ((sorted? (cdr l)))
  )
)


(define (max_ l)
  (cond ((null? l) 0)
        ((= (length l) 1) (car l))
        ((> (car l) (cadr l)) (max_ (cons (car l) (cddr l))))
        ((max_ (cdr l)))
  )
)

; 3 1 2 5 6
; 6

(define (filter_ func l)
  (cond ((null? l) '())
      ((func (car l)) (cons (car l) (filter_ func (cdr l))))
      ((filter_ func (cdr l)))
  )
)



(define (max_divisible3 l)
  (max_ (filter_ (lambda (n) (= (remainder n 3) 0)) l))  
)

(define (range k)
  (if (= k 0) '()
    (append (range (- k 1)) (list k))
  )
)

(define (pow a n)
  (if (= n 0) 1
    (* (pow a (- n 1)) a)
  )
)

(define (generate_powers a k)
  (map (lambda (p) (pow a p)) (range k))
)

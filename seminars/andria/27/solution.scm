;1
(define (reverse_ lst)
    (if (null? lst)
        lst
        (append (reverse_ (cdr lst)) (list (car lst))) 
    )
)

;2
(define (sorted? lst)
    (if (or (null? lst) (null? (cdr lst)))
        #t
        (if (< (car lst) (cadr lst))
            (sorted? (cdr lst))
            #f
        )
    )

    ; (apply < lst) ; => (eval (cons fun lst))

    ; (cond 
    ;     ((or (null? lst) (null? (cdr lst))) #t)
    ;     ((< (car lst) (cadr lst)) (sorted? (cdr lst)))
    ;     (#f)
    ; )
)

;3
(define (max_ lst)
    (if (null? lst)
        0
        (if (< (car lst) (max_ (cdr lst)))
           (max_ (cdr lst))
           (car lst)
        )
    )
)

(define (filter_ func lst)
    (if (null? lst)
        lst
        (if (func (car lst))
            (cons (car lst) (filter_ func (cdr lst)))
            (filter_ func (cdr lst))
        )
    )
)

(define (divisible3? num)
    (zero? (remainder num 3))
)

(define (max_divisible3 lst)
    (max_ (filter_ divisible3? lst))
)

;4
(define (range k)
    (if (zero? k)
        `()
        (append (range (- k 1)) (list k))
    )
)

(define (pow a n)
    (if (= n 1)
        a
        (* a (pow a (- n 1)))
    )
)

(define (aaaaaa! a k)
    (if (zero? k)
        `()
        (cons a (aaaaaa! a (- k 1)))
    )
)

(define (generate_powers a k)
    (map pow (aaaaaa! a k) (range k))
    ; (map (lambda (elem) (pow a elem)) (range k))
)

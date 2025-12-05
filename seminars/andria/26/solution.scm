; 1
(define (first-elem lst)
    (if (null? lst)
        "None"
        (car lst)
    )
    ; (cond 
    ;     ((null? lst) "None")
    ;     ((car lst))
    ; )
)

; 2
(define (abs_ x)
    (if (< x 0)
        (- x)       ; same as (- 0 x)
        x
    )
)

; 3
(define (right-triangle lst)
    (= 
        (+ (square (car lst)) (square (cadr lst))) 
        (square (caddr lst))
    )
)

; 4
(define (last-elem lst)
    (if (null? lst)
        "None"
        (if (null? (cdr lst))
            (car lst)
            (last-elem (cdr lst))
        )
    )
)

; 5
(define (length_ lst)
    (if (null? lst)
        0
        (+ 1 (length_ (cdr lst)))
    )
)

; 6
(define (k-th-element lst k)
    (if (null? lst)
        "None"
        (if (= k 0)
            (car lst)
            (k-th-element (cdr lst) (- k 1))
        )
    )
)

; 7
(define (filter-range lst a b)
    (if (null? lst)
        lst
        (if (or 
                (and (>= (car lst) a) (<= (car lst) b))
                (and (<= (car lst) a) (>= (car lst) b))
            )
            (cons (car lst) (filter-range (cdr lst) a b))
            (filter-range (cdr lst) a b)
        )
    )
)

; 8
(define (prime-helper n div)
    (if (= n div)
        #t
        (if (= 0 (remainder n div))
            #f
            (prime-helper n (+ 1 div))
        )
    )
)

(define (prime? n)
    (if (= n 1)
        #f
        (prime-helper n 2)
    )
)

; 9
(define (primes? lst)
    (if (null? lst)
        lst
        (cons (prime? (car lst)) (primes? (cdr lst)))
    )
)
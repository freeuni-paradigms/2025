; reverse and duplicate list
(define (reverseDup lst)
    ; (append (reverse lst) (reverse lst))
    (let
        ((reversed (reverse lst)))
        (append reversed reversed)
    )
)


; a^b in O(log(n))

; b % 2 == 0 => (a^2)^(b / 2)
; b % 2 == 1 => a * (a^2)^((b - 1) / 2)
(define (binpow a b)
    (if (zero? b)
        1
        (if (zero? (remainder b 2))
            (binpow (* a a) (/ b 2))
            (* a (binpow (* a a) (/ (- b 1) 2)))
        )
    )
)


; fibonacci
(define (fib n)
    (let loop
        ((prev 0) (curr 1) (idx 1))
        (if (zero? n)
            0
            (if (= n idx)
                curr
                (loop curr (+ prev curr) (+ idx 1))
            )
        )
    )
)

;4
(define (compare n lst cmp)
    (if (null? lst)
        `()
        (if (cmp (car lst) n)
            (cons (car lst) (compare n (cdr lst) cmp))
            (compare n (cdr lst) cmp)
        )
    )
)

; (define (partition n lst)
;     (list (compare n lst <) (compare n lst >=))
; )

(define (partition n lst)
    (let loop
        ((less `()) (more `()) (curr_lst lst))
        (if (null? curr_lst)
            (list less more)
            (if (< (car curr_lst) n)
                (loop (append less (list (car curr_lst))) more (cdr curr_lst))
                (loop less (append more (list (car curr_lst))) (cdr curr_lst))
            )
        )
    )
)


; is lst2 permutation of lst1
(define (contains?_cut n lst)
    (if (null? lst)
        `()
        (if (= n (car lst))
            (cdr lst)
            (cons (car lst) (contains?_cut n (cdr lst)))
        )
    )
)

(define (permutation? lst1 lst2)
    (if (= (length lst1) (length lst2))
        (if (null? lst1)
            #t
            (permutation? (cdr lst1) (contains?_cut (car lst1) lst2))
        )
        #f
    )
)


; isWay with bfs
(define (isWay? edges start finish)
)

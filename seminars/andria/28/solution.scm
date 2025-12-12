; 1
(define (digits a)
    (if (< a 10)
        (list a)
        (append (digits (div a 10)) (list (remainder a 10)))
    )    
)

(define (list_power lst)
    (map (lambda (elem) (expt elem (length lst))) lst)
)

(define (sum lst)
    (apply + lst)
)

(define (narcisisstic? n)
    (= n (sum (list_power (digits n))))
)

; 2
(define (count a lst)
    (if (null? lst)
        0
        (if (= a (car lst))
            (+ 1 (count a (cdr lst)))
            (count a (cdr lst))
        )
    )
)

;; SEMINAR 1 SOLUTION

; (define (set_helper lst visited)
;     (if (null? lst)
;         visited
;         (if (= 1 (count (car lst) visited))
;             (set_helper (cdr lst) visited)
;             (set_helper (cdr lst) (cons (car lst) visited))
;         )
;     )
; )

; (define (set lst)
;     (set_helper lst `())
; )

;; SEMINAR 2 SOLUTION

; ; helper
; (define (contains elem lst)
;     (if (null? lst)
;         #f
;         (if (= (car lst) elem)
;             #t
;             (contains elem (cdr lst))
;         )
;     )
; )

; (define (set lst)
;     (if (null? lst)
;         `()
;         (if (contains (car lst) (cdr lst))
;             (set (cdr lst))
;             (cons (car lst) (set (cdr lst)))
;         )
;     )
; )

;; SOLUTION WITHOUT HELPER

(define (set lst)
    (if (null? lst)
        `()
        (if (zero? (count (car lst) (set (cdr lst))))
            (cons (car lst) (set (cdr lst)))
            (set (cdr lst))
        )
    )
)

(define (frequency lst)
    (map (lambda (elem) (list elem (count elem lst))) (set lst))
)

; 3
(define (multiply_helper n elem)
    (if (zero? n)
        `()
        (cons elem (multiply_helper (- n 1) elem))
    )
)

(define (multiply n lst)
    (apply append (map (lambda (elem) (multiply_helper n elem)) lst))
)

; 4
(define (ksubset n lst)
    (if (zero? n)
        `(())
        (if (< (length lst) n)
            `()
            (append 
                (map 
                    (lambda (subset) (cons (car lst) subset)) 
                    (ksubset (- n 1) (cdr lst))
                )
                (ksubset n (cdr lst))
            )
        )
    )
)

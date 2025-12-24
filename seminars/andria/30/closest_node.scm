(define (closest-node lst)
    (if (null? lst)
        0
        (if (null? (cadr lst))
            (car lst)
            (+ (car lst) (apply min (map closest-node (cadr lst))))
        )
    )
)
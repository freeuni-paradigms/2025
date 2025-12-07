(define (first-elem list) 
        (if (null? list) "None"
        (car list)))

(define (abs_ num)
        (if (< num 0) (* -1 num)
        num))

(define (right-triangle list)
        (= (+ (* (car list) (car list)) (* (cadr list) (cadr list)))
        (* (caddr list) (caddr list))))

(define (last-elem list)
        (if (null? list) "None"
          (if (= 1 (length list)) (car list)
            (last-elem (cdr list))
          )
        )  
)

(define (length_ list)
        (if (null? list) 0
          (+ 1 (length_ (cdr list)))
        )
)

(define (k-th-element list k)
        (if (< k (length list))
          (if (= k 0) (car list)
          (k-th-element (cdr list) (- k 1)))
          "None"
        )
)

(define (filter-range-helper a b list final-list)
        (if (null? list) '()
          (if (and (<= (car list) b) (>= (car list) a))
             (filter-range-helper a b (cdr list) (cons (car list) final-list))
          (filter-range-helper a b (cdr list) final-list)
        )
      )
)

(define (filter-range list a b)
        (filter-range-helper a b list '())
)

(define (min_ l)
  (if (null? l) 0
     (apply min l)
  )
)

(define (closest-node l) 
  (cond
      ((null? l) 0)
      (else (+ (car l) (min_ (map (lambda (e) (closest-node e)) (cadr l)))))
  )
)

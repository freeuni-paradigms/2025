(define (contains l e)
  (> (apply + (map (lambda (x) (if (= x e) 1 0)) l)) 0)
)

(define (concat-unique l1 l2)
  (apply append (map (lambda (e1 e2) (if (contains l2 e1) (list e2) (list e1 e2))) l1 l2))
)

(define (unique-sums-helper l)
  (if (null? l) '(0)
    (let ((last (unique-sums-helper (cdr l))))
      (concat-unique (map (lambda (e) (+ (car l) e)) last) last)
    )
  )
)

(define (unique-sums l)
  (length (unique-sums-helper l))
)

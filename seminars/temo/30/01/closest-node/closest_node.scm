;      1
;     / \
;    2   4     =>  5 = 1 + 4
;   /
;  3

;(1 ((2 ((3 ()))) (4 ())))

(define (closest-node tree)
  (if (null? tree) 0
    (+ (car tree) 
       (if (null? (cadr tree)) 0
         (apply min (map (lambda (e) (closest-node e)) (cadr tree)))
       )
    )
  )
)
